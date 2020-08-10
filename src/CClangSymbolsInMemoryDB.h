
#ifndef _CClangSymbolsInMemoryDB_H_
#define _CClangSymbolsInMemoryDB_H_

#include <vector>
#include <string>
#include <memory>
#include "CClangParser.h"
#include "CObjectStore.h"
#include "CObjectIndex.h"

namespace gintel
{
	namespace storage
	{
		class CClangSymbolsInMemoryDB
		{
			public:
				void add(std::shared_ptr<IStoreObject> symbol);
				std::vector<std::shared_ptr<gintel::modules::CClangParser::CObjectInfo>> search(const std::string& keyword);
				std::vector<std::shared_ptr<gintel::modules::CClangParser::CObjectInfo>> typeAheadSuggestions(const std::string& keyword);

			private:
				CObjectStore m_store;
				CObjectIndex m_index;
		};
	}
}

#endif	//	_CClangSymbolsInMemoryDB_H_

