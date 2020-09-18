
#ifndef _CGINTELENGINE_H_
#define _CGINTELENGINE_H_

#include <filesystem>
#include <vector>
#include <string>
#include <memory>
#include <map>
#include "CClangSymbolsInMemoryDB.h"
#include "IGintelEngine.h"

namespace gintel
{
	namespace storage
	{
		class CSymbolInfo;
		class CClangSymbolsInMemoryDB;
	}

	namespace modules
	{
		class CGintelEngine : public IGintelEngine
		{
			public:
				virtual void addProject(const SourceProject& project) override;
				virtual void rebuildSymbolsDB() override;
				virtual std::vector<std::shared_ptr<gintel::storage::CSymbolInfo>> searchSymbol(
					const std::string& keyword) override;

			private:
				void processProject(const SourceProject& project);
				void addSymbolToDB(
					std::shared_ptr<gintel::storage::CSymbolInfo> objInfo,
					const SourceProject& project);
				
			public:
				CGintelEngine();
				~CGintelEngine() = default;
				CGintelEngine(const CGintelEngine&) = delete;
				CGintelEngine& operator =(const CGintelEngine&) = delete;

			private:
				static std::vector<std::string> SOURCE_FILE_EXTENSIONS;

			private:
				std::map<std::string, SourceProject> m_projectsList;
				std::unique_ptr<gintel::storage::CClangSymbolsInMemoryDB> m_symbolsDB;
		};
	}
}

#endif	//	_CGINTELENGINE_H_

