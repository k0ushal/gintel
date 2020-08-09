
#ifndef _CClangSymbolsInMemoryDB_H_
#define _CClangSymbolsInMemoryDB_H_

#include <vector>
#include <string>
#include <memory>
#include "IStoreObject.h"
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
				std::vector<std::shared_ptr<IStoreObject>> search(const std::string& keyword);
				std::vector<std::shared_ptr<IStoreObject>> typeAheadSuggestions(const std::string& keyword);

			private:
				CObjectStore m_store;
				CObjectIndex m_index;
		};
	}
}

#endif	//	_CClangSymbolsInMemoryDB_H_

