
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
using gintel::modules::ProjectItem;

std::vector<std::string> CGintelEngine::SOURCE_FILE_EXTENSIONS = { ".cpp", ".c", ".h", ".hxx", ".hpp" };

void CGintelEngine::processProject(
	const ProjectItem& project
	)
{
	CSourceEnumerator enumerator;

	enumerator.addEnumerableFileExtensions(SOURCE_FILE_EXTENSIONS);

	auto lambda = [](const CClangParser::ObjectInfo& objInfo, void* context) -> bool {

#if 1
	std::map<CClangParser::ObjectType, std::string> obTypeMap;
	obTypeMap[CClangParser::ObjectType::Class] = "Class";
	obTypeMap[CClangParser::ObjectType::GlobalFunction] = "Function";
	obTypeMap[CClangParser::ObjectType::Method] = "Method";
#endif
		
		auto prj {reinterpret_cast<ProjectItem*>(context)};
		std::cout << "\t" << prj->projectName << ":: [" << obTypeMap[objInfo.type] << "] " << objInfo.name << ", " << objInfo.location.file.filename() << std::endl;
		return true;
	};

	//	Pass this directory to source enumerator
	enumerator.enumerate(project.srcDirPath, [&](const std::filesystem::path& filePath) -> bool {

		CClangParser clParser;

		//	For every file returned by the enumerator,
		//	parse it using clang to find source symbols
		std::cout << "Parsing file [" << filePath.filename() << "]" << std::endl;
		clParser.parseSourceFile(filePath, lambda, const_cast<ProjectItem*>(&project));
		std::cout << std::endl;

		return true;
	});

	//	add each of these symbols to our database.
}


void CGintelEngine::addProject(const ProjectItem& project)
{
	m_projectsList.emplace(project.projectName, project);
}

void CGintelEngine::start()
{
	for (auto& project : m_projectsList)
	{
		std::cout << "Process project (" << project.first << ")" << std::endl;
		processProject(project.second);
	}
}
