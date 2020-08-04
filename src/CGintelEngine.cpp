
#include <map>
#include <iostream>
#include <functional>
#include <filesystem>
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
	auto symbolsProcessor = [this](const CClangParser::ObjectInfo& objInfo, void* context) -> bool {
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
	const CClangParser::ObjectInfo& objInfo,
	const SourceProject& project)
{
#if !DEBUG_LOGS
	std::map<CClangParser::ObjectType, std::string> obTypeMap;
	obTypeMap[CClangParser::ObjectType::Class] = "Class";
	obTypeMap[CClangParser::ObjectType::GlobalFunction] = "Function";
	obTypeMap[CClangParser::ObjectType::Method] = "Method";

	std::cout << "\t" << project.projectName << ":: [" << obTypeMap[objInfo.type] << "] " << objInfo.name << ", " << objInfo.location.file.filename() << std::endl;
#endif
}

