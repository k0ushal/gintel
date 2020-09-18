/*

clang++ ex3.cpp $(llvm-config-10 --cxxflags) $(llvm-config-10 --ldflags --libs --system-libs) -lclang

*/

#include <clang-c/Index.h>

#include <iostream>

int count = 0;

CXChildVisitResult visitor(CXCursor cursor, CXCursor, CXClientData) {

	auto isMainFile = clang_Location_isFromMainFile(clang_getCursorLocation(cursor));
	if (!isMainFile)
	{
		return CXChildVisit_Continue;
	}

	CXCursorKind kind = clang_getCursorKind(cursor);

	// Consider functions and methods
	if (kind == CXCursorKind::CXCursor_FunctionDecl ||
			kind == CXCursorKind::CXCursor_CXXMethod) {
		auto cursorName = clang_getCursorDisplayName(cursor);

		// Print if function/method starts with doSomething
		auto cursorNameStr = std::string(clang_getCString(cursorName));
		// if (cursorNameStr.find("doSomething") == 0) {
		if (true) {
			// Get the source locatino
			CXSourceRange range = clang_getCursorExtent(cursor);
			CXSourceLocation location = clang_getRangeStart(range);

			CXFile file;
			unsigned line;
			unsigned column;
			clang_getFileLocation(location, &file, &line, &column, nullptr);

			auto fileName = clang_getFileName(file);

			std::cout << "Found call to " << clang_getCString(cursorName) << " at "
				<< line << ":" << column << " in " << clang_getCString(fileName)
				<< std::endl;

			clang_disposeString(fileName);
		}

		clang_disposeString(cursorName);
	}

	return CXChildVisit_Recurse;
}

int main(int argc, char **argv) {
	if (argc < 2) {
		return 1;
	}

	// Command line arguments required for parsing the TU
	constexpr const char *ARGUMENTS[] = {};

	// Create an index with excludeDeclsFromPCH = 1, displayDiagnostics = 0
	CXIndex index = clang_createIndex(1, 0);

	// Speed up parsing by skipping function bodies
	CXTranslationUnit translationUnit = clang_parseTranslationUnit(
			index, argv[1], ARGUMENTS, std::extent<decltype(ARGUMENTS)>::value,
			nullptr, 0, CXTranslationUnit_SkipFunctionBodies);

	// Visit all the nodes in the AST
	CXCursor cursor = clang_getTranslationUnitCursor(translationUnit);
	clang_visitChildren(cursor, visitor, 0);

	// Release memory
	clang_disposeTranslationUnit(translationUnit);
	clang_disposeIndex(index);

	std::cout << "Count = " << count << std::endl;

	return 0;
}
