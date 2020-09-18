
#include <memory>
#include <any>
#include "IStoreObject.h"
#include "CObjectStore.h"

using gintel::storage::CObjectStore;
using gintel::storage::IStoreObject;

std::any CObjectStore::add(std::shared_ptr<IStoreObject> object)
{
	if (!object.use_count())
	{
		throw std::invalid_argument("NULL argument");
	}
	
	auto obCopy {object->clone()};
	auto itr = m_store.emplace(m_store.end(), obCopy);
	return itr;
}

void CObjectStore::remove(std::any objectId)
{
	throw std::bad_function_call();
}

std::shared_ptr<IStoreObject> CObjectStore::get(std::any objectId)
{
	auto iter {std::any_cast<std::list<std::shared_ptr<IStoreObject>>::iterator>(objectId)};
	return *iter;
}
