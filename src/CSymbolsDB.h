
#ifndef _CSYMBOLSDB_H_
#define _CSYMBOLSDB_H_

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
		class CSymbolsDB
		{
			public:
				void add(std::shared_ptr<IStoreObject> symbol);
				std::vector<std::shared_ptr<IStoreObject>> search(const std::string& keyword);
				std::vector<std::shared_ptr<IStoreObject>> getSuggestions(const std::string& keyword);

			private:
				CObjectStore m_store;
				CObjectIndex m_index;
		};
	}
}

#endif	//	_CSYMBOLSDB_H_

