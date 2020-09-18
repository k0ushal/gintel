
#ifndef _COBJECT_STORE_H_
#define _COBJECT_STORE_H_

#include <list>
#include <memory>
#include <any>

namespace gintel
{
	namespace storage
	{
		class IStoreObject;

		class CObjectStore
		{
			public:
				//	returns opaque object id
				//	pass this object id to remove and search.
				std::any add(std::shared_ptr<IStoreObject> object);

				void remove(std::any objectId);
				std::shared_ptr<IStoreObject> get(std::any objectId);

			private:
				std::list<std::shared_ptr<IStoreObject>> m_store;
		};
	}
}


#endif	//	_COBJECT_STORE_H_

