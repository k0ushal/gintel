
#include <map>
#include <iostream>
#include <functional>
#include <filesystem>
#include <algorithm>
#include "CObjectStore.h"
#include "CObjectIndex.h"
#include "CClangSymbolsInMemoryDB.h"
#include "CGintelEngine.h"
#include "CSourceEnumerator.h"
#include "CClangParser.h"
#include "CSymbolInfo.h"

using gintel::modules::CGintelEngine;
using gintel::modules::CSourceEnumerator;
using gintel::modules::CClangParser;
using gintel::modules::SourceProject;
using gintel::storage::CClangSymbolsInMemoryDB;
using gintel::storage::CSymbolInfo;

std::vector<std::string> CGintelEngine::SOURCE_FILE_EXTENSIONS = { ".cpp", ".c", ".h", ".hxx", ".hpp" };

CGintelEngine::CGintelEngine()
{
	m_symbolsDB = std::make_unique<CClangSymbolsInMemoryDB>();
}

void CGintelEngine::processProject(
	const SourceProject& project
	)
{
	CSourceEnumerator enumerator;

	//	set up the enumerator
	enumerator.addEnumerableFileExtensions(SOURCE_FILE_EXTENSIONS);

	//	processing logic for each symbol found
	auto symbolsProcessor = [this](std::shared_ptr<CSymbolInfo> objInfo, void* context) -> bool {
		auto prj {reinterpret_cast<SourceProject*>(context)};
		addSymbolToDB(objInfo, *prj);
		return true;
	};

	//	Pass this directory to source enumerator
	enumerator.enumerate(project.srcDirPath, [&](const std::filesystem::path& filePath) -> bool {
		CClangParser clParser;
		clParser.parseSourceFile(filePath, symbolsProcessor, const_cast<SourceProject*>(&project));
		return true;
		});
}

void CGintelEngine::addProject(const SourceProject& project)
{
	m_projectsList.emplace(project.projectName, project);
	processProject(project);
}

void CGintelEngine::rebuildSymbolsDB()
{
	for (auto& project : m_projectsList)
	{
		std::cout << "Process project (" << project.first << ")" << std::endl;
		processProject(project.second);
	}
}

void CGintelEngine::addSymbolToDB(
	std::shared_ptr<CSymbolInfo> objInfo,
	const SourceProject& project)
{
#if DEBUG_LOGS
	std::map<SymbolType, std::string> obTypeMap;
	obTypeMap[SymbolType::Class] = "Class";
	obTypeMap[SymbolType::GlobalFunction] = "Function";
	obTypeMap[SymbolType::Method] = "Method";

	std::cout << "\t" << project.projectName << ":: [" << obTypeMap[objInfo->m_type] << "] " << objInfo->m_name << ", " << objInfo->m_location.file.filename() << std::endl;
#endif

	m_symbolsDB->add(objInfo);
}

std::vector<std::shared_ptr<CSymbolInfo>>
CGintelEngine::searchSymbol(
	const std::string& keyword)
{
	std::vector<std::shared_ptr<CSymbolInfo>> result;

	auto temp {m_symbolsDB->search(keyword)};
	std::for_each(temp.begin(), temp.end(), [&](const auto object) {

		result.push_back(std::dynamic_pointer_cast<CSymbolInfo>(object));
	});

	return result;
}
