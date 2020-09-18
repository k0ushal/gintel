
#include <map>
#include <iostream>
#include <functional>
#include <filesystem>
#include <algorithm>
#include "CGintelEngine.h"
#include "CSourceEnumerator.h"
#include "CClangParser.h"

using gintel::modules::CGintelEngine;
using gintel::modules::CSourceEnumerator;
using gintel::modules::CClangParser;
using gintel::modules::SourceProject;

std::vector<std::string> CGintelEngine::SOURCE_FILE_EXTENSIONS = { ".cpp", ".c", ".h", ".hxx", ".hpp" };

void CGintelEngine::processProject(
	const SourceProject& project
	)
{
	CSourceEnumerator enumerator;

	//	set up the enumerator
	enumerator.addEnumerableFileExtensions(SOURCE_FILE_EXTENSIONS);

	//	processing logic for each symbol found
	auto symbolsProcessor = [this](std::shared_ptr<CClangParser::CObjectInfo> objInfo, void* context) -> bool {
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
	std::shared_ptr<CClangParser::CObjectInfo> objInfo,
	const SourceProject& project)
{
#if DEBUG_LOGS
	std::map<CClangParser::ObjectType, std::string> obTypeMap;
	obTypeMap[CClangParser::ObjectType::Class] = "Class";
	obTypeMap[CClangParser::ObjectType::GlobalFunction] = "Function";
	obTypeMap[CClangParser::ObjectType::Method] = "Method";

	std::cout << "\t" << project.projectName << ":: [" << obTypeMap[objInfo->m_type] << "] " << objInfo->m_name << ", " << objInfo->m_location.file.filename() << std::endl;
#endif

	m_symbolsDB.add(objInfo);
}

std::vector<std::shared_ptr<CClangParser::CObjectInfo>>
CGintelEngine::searchSymbol(
	const std::string& keyword)
{
	std::vector<std::shared_ptr<CClangParser::CObjectInfo>> result;

	auto temp {m_symbolsDB.search(keyword)};
	std::for_each(temp.begin(), temp.end(), [&](const auto object) {

		result.push_back(std::dynamic_pointer_cast<CClangParser::CObjectInfo>(object));
	});

	return result;
}
