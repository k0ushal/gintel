
/*

clang++ ex3.cpp $(llvm-config-10 --cxxflags) $(llvm-config-10 --ldflags --libs --system-libs) -lclang

*/

#include <iostream>
#include <algorithm>
#include "CGintelEngine.h"
#include "CClangParser.h"

using gintel::modules::CGintelEngine;
using gintel::modules::SourceProject;
using gintel::modules::CClangParser;
using std::cout;
using std::endl;

std::string obTypeName(CClangParser::ObjectType type)
{
	switch (type)
	{
		case CClangParser::ObjectType::Method:
			return "[Method]";

		case CClangParser::ObjectType::Class:
			return "[Class]";

		case CClangParser::ObjectType::GlobalFunction:
			return "[Function]";
	}

	return "[]";
}

int main()
{
	CGintelEngine engine;
	auto currentDir {std::filesystem::current_path()};

	engine.addProject(SourceProject{"Shape", currentDir / "target_sources" / "shape"});
	engine.rebuildSymbolsDB();

	auto result {engine.searchSymbol("Shape")};
	std::for_each(result.begin(), result.end(), [&](const std::shared_ptr<CClangParser::CObjectInfo> object) {
		auto fullPath {object->m_location.file.string()};
		auto pos {fullPath.find(currentDir.string())};
		fullPath = fullPath.erase(pos, currentDir.string().length());

		cout << obTypeName(object->m_type) << object->m_name
		 << ", [" << fullPath << "]" << endl;
	});

	return 0;
}

