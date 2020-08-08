
#ifndef _CGINTELENGINE_H_
#define _CGINTELENGINE_H_

#include <filesystem>
#include <vector>
#include <string>
#include <map>
#include "CClangParser.h"

namespace gintel
{
	namespace modules
	{
		struct SourceProject
		{
			std::string projectName;
			std::filesystem::path srcDirPath;
		};

		class CGintelEngine
		{
			public:
				void addProject(const SourceProject& project);
				void rebuildSymbolsDB();

			private:
				void processProject(const SourceProject& project);
				void addSymbolToDB(
					const CClangParser::CObjectInfo& objInfo,
					const SourceProject& project);
				
			public:
				CGintelEngine() = default;
				~CGintelEngine() = default;
				CGintelEngine(const CGintelEngine&) = delete;
				CGintelEngine& operator =(const CGintelEngine&) = delete;

			private:
				static std::vector<std::string> SOURCE_FILE_EXTENSIONS;
				std::map<std::string, SourceProject> m_projectsList;
		};
	}
}

#endif	//	_CGINTELENGINE_H_

