
#ifndef _CGINTELENGINE_H_
#define _CGINTELENGINE_H_

#include <filesystem>
#include <vector>
#include <string>
#include <map>
#include "CClangParser.h"
#include "CClangSymbolsInMemoryDB.h"
#include "GintelDataStruct.h"

namespace gintel
{
	namespace modules
	{
		class CGintelEngine
		{
			public:
				void addProject(const SourceProject& project);
				void rebuildSymbolsDB();
				std::vector<std::shared_ptr<CClangParser::CObjectInfo>> searchSymbol(
					const std::string& keyword);

			private:
				void processProject(const SourceProject& project);
				void addSymbolToDB(
					std::shared_ptr<CClangParser::CObjectInfo> objInfo,
					const SourceProject& project);
				
			public:
				CGintelEngine() = default;
				~CGintelEngine() = default;
				CGintelEngine(const CGintelEngine&) = delete;
				CGintelEngine& operator =(const CGintelEngine&) = delete;

			private:
				static std::vector<std::string> SOURCE_FILE_EXTENSIONS;
				std::map<std::string, SourceProject> m_projectsList;
				gintel::storage::CClangSymbolsInMemoryDB m_symbolsDB;
		};
	}
}

#endif	//	_CGINTELENGINE_H_

