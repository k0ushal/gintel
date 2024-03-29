

/*

clang++ ex3.cpp $(llvm-config-10 --cxxflags) $(llvm-config-10 --ldflags --libs --system-libs) -lclang

*/

#include <map>
#include <clang-c/Index.h>
#include <iostream>
#include <filesystem>
#include "CClangParser.h"
#include "CClangUtil.h"
#include "CSymbolInfo.h"
#include "IGintelEngine.h"

using gintel::modules::CClangParser;
using gintel::modules::CClangUtil;
using gintel::modules::SourceProject;
using gintel::storage::CSymbolInfo;
using gintel::storage::SymbolType;

struct VisitorContext
{
	std::function<bool(std::shared_ptr<CSymbolInfo>, void*)> callback;
	void* callbackCtx;
};

CXChildVisitResult visitor(
	CXCursor cursor,
	CXCursor parent,
	CXClientData context
	)
{
	auto visitorCtx {reinterpret_cast<VisitorContext*>(context)};
	SourceProject* sourceProject {reinterpret_cast<SourceProject*>(visitorCtx->callbackCtx)};

	auto isMainFile = clang_Location_isFromMainFile(clang_getCursorLocation(cursor));
	if (!isMainFile)
	{
		return CXChildVisit_Continue;
	}

	//	cursor kind mapping
	std::map<CXCursorKind, SymbolType> cursorKindMap;
	cursorKindMap[CXCursorKind::CXCursor_FunctionDecl] = SymbolType::GlobalFunction;
	cursorKindMap[CXCursorKind::CXCursor_ClassDecl] = SymbolType::Class;
	cursorKindMap[CXCursorKind::CXCursor_CXXMethod] = SymbolType::Method;

	CXCursorKind kind {clang_getCursorKind(cursor)};

	//	Object info generation
	auto prepareObject {[&](CXCursor cur, CXCursor parent) -> std::shared_ptr<CSymbolInfo> {

		std::string curName;
		if (kind == CXCursorKind::CXCursor_CXXMethod)
		{
			curName = CClangUtil::getCursorName(parent) + "::";
		}
		curName += CClangUtil::getCursorName(cur);
		auto curKind {cursorKindMap[kind]};
		auto filePath {CClangUtil::getCursorFileLocation(cur)};

		return std::make_shared<CSymbolInfo>(sourceProject->projectName, curName, curKind, filePath);
	}};

	//	Only indicate objects of interest to the caller
	if (cursorKindMap.find(kind) != cursorKindMap.end())
	{
		auto obInfo {prepareObject(cursor, parent)};

		//	indicate this object to the caller
		auto callbackRet {visitorCtx->callback(obInfo, visitorCtx->callbackCtx)};
		if (!callbackRet)
		{
			return CXChildVisit_Break;
		}
	}

	return CXChildVisit_Recurse;
}

void CClangParser::parseSourceFile(
	const std::filesystem::path& filePath,
	std::function<bool(std::shared_ptr<CSymbolInfo>, void*)> callback,
	void* context
	)
{
	// Command line arguments required for parsing the TU
	//constexpr const char *ARGUMENTS[] = {"-fms-compatibility", "-fsyntax-only", "--", "-x", "c++"};
	constexpr const char *ARGUMENTS[] = {"-x", "c++"};

	// Create an index with excludeDeclsFromPCH = 1, displayDiagnostics = 0
	CXIndex index = clang_createIndex(1, 0);

	// Speed up parsing by skipping function bodies
	CXTranslationUnit translationUnit = clang_parseTranslationUnit(
			index, filePath.string().c_str(), ARGUMENTS, std::extent<decltype(ARGUMENTS)>::value,
			nullptr, 0, CXTranslationUnit_SkipFunctionBodies | CXTranslationUnit_KeepGoing | 
			CXTranslationUnit_LimitSkipFunctionBodiesToPreamble | CXTranslationUnit_IgnoreNonErrorsFromIncludedFiles);

	// Visit all the nodes in the AST
	CXCursor cursor = clang_getTranslationUnitCursor(translationUnit);

	VisitorContext clientData;
	clientData.callback = callback;
	clientData.callbackCtx = context;

	clang_visitChildren(
		cursor,
		visitor,
		&clientData);

	// Release memory
	clang_disposeTranslationUnit(translationUnit);
	clang_disposeIndex(index);
}

