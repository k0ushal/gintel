
#ifndef _CClangSymbolsInMemoryDB_H_
#define _CClangSymbolsInMemoryDB_H_

#include <vector>
#include <string>
#include <memory>
#include "CObjectIndex.h"
#include "CObjectStore.h"

namespace gintel
{
	namespace storage
	{
		class CObjectIndex;
		class CObjectStore;
		class CSymbolInfo;

		class CClangSymbolsInMemoryDB
		{
			public:
				CClangSymbolsInMemoryDB();

				void add(std::shared_ptr<gintel::storage::CSymbolInfo> symbol);
				std::vector<std::shared_ptr<gintel::storage::CSymbolInfo>> search(const std::string& keyword);
				std::vector<std::shared_ptr<gintel::storage::CSymbolInfo>> typeAheadSuggestions(const std::string& keyword);

			private:
				std::unique_ptr<CObjectStore> m_store;
				std::unique_ptr<CObjectIndex> m_index;
		};
	}
}

#endif	//	_CClangSymbolsInMemoryDB_H_

