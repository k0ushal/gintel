
#ifndef _COBJECT_INDEX_H_
#define _COBJECT_INDEX_H_


#include <map>
#include <vector>
#include <string>
#include <any>

namespace gintel
{
	namespace storage
	{
		class CObjectIndex
		{
			public:
				void add(const std::string& key, std::any value);
				std::vector<std::any> search(const std::string& key);
				std::vector<std::any> typeAheadSuggestions(const std::string& key);

			public:
				CObjectIndex() = default;
				~CObjectIndex() = default;

			private:
				std::map<std::string, std::vector<std::any>> m_index;
		};
	}
}

#endif	//	_COBJECT_INDEX_H_
