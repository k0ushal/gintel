
/*

clang++ ex3.cpp $(llvm-config-10 --cxxflags) $(llvm-config-10 --ldflags --libs --system-libs) -lclang

*/

#include <unordered_set>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include "CGintelEngine.h"
#include "CClangParser.h"

using gintel::modules::CGintelEngine;
using gintel::modules::SourceProject;
using gintel::modules::CClangParser;
using std::cout;
using std::endl;

std::string obNameFromType(CClangParser::ObjectType type)
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

void print(
	const std::filesystem::path& sourcePathPrefix,
	const std::vector<std::shared_ptr<CClangParser::CObjectInfo>> &objects
	)
{
	std::for_each(objects.begin(), objects.end(), [&](const std::shared_ptr<CClangParser::CObjectInfo> object) {
		auto fullPath{object->m_location.file.string()};
		auto pos{fullPath.find(sourcePathPrefix.string())};
		fullPath = fullPath.erase(pos, sourcePathPrefix.string().length());

		cout << object->m_project << ": " << obNameFromType(object->m_type) << " " << object->m_name
			 << ", [" << fullPath << "]" << endl;
	});
}

void printHelp()
{
	cout << endl << endl;
	cout << "Usage:" << endl;

	cout << "    add <project-name> <source-dir-path>" << endl;
	cout << "    Adds a project to the database and builds an index over it" << endl << endl;

	cout << "    search <keyword>" << endl;
	cout << "    Searches the keyword in the store and returns all relevant items" << endl << endl;

	cout << "    help" << endl;
	cout << "    Prints this help text" << endl << endl;
}

int main()
{
	CGintelEngine engine;
	auto currentDir {std::filesystem::current_path()};
	std::unordered_set<std::string> allowedArgs {"add", "search", "help", "exit"};

	printHelp();
	std::vector<std::string> args;

	do
	{
		args.clear();
		std::string arg;
		std::string buff;

		std::getline(std::cin, buff);
		std::istringstream userInput(buff);
		while (std::getline(userInput, arg, ' '))
		{
			args.push_back(arg);
		}

		if (args.empty())
		{
			continue;
		}

		if (allowedArgs.count(args[0]) == 0)
		{
			cout << "Invalid command [" << args[0] << "]" << endl;
			printHelp();
			continue;
		}

		if (args[0] == "add")
		{
			if (args.size() < 3)
			{
				cout << "Missing args for [add] command" << endl;
				printHelp();
				continue;
			}

			if (!std::filesystem::exists(args[2]) || !std::filesystem::is_directory(args[2]))
			{
				cout << "Error:: Please check that the <source-dir-path> exists and points to a directory" << endl;
				continue;
			}

			auto fpath {std::filesystem::canonical(args[2])};
			engine.addProject(SourceProject{args[1], fpath});
		}
		else if (args[0] == "search")
		{
			if (args.size() < 2 || args[1].empty())
			{
				cout << "Missing args for [search] command" << endl;
				printHelp();
				continue;
			}

			auto result {engine.searchSymbol(args[1])};
			auto sourcePathPrefix {std::filesystem::current_path() / "target_sources"};

			print(sourcePathPrefix, result);
		}

	} while (args[0] != "exit");

	return 0;
}

