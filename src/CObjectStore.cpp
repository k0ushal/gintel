
#include <memory>
#include <any>
#include "IStoreObject.h"
#include "CObjectStore.h"

using gintel::storage::CObjectStore;
using gintel::storage::IStoreObject;


std::any CObjectStore::add(std::shared_ptr<IStoreObject> object)
{
	auto obCopy {object->clone()};
	auto itr = m_store.emplace(m_store.end(), obCopy);
	return itr;
}

void CObjectStore::remove(void* objectId)
{
}

std::shared_ptr<IStoreObject> CObjectStore::get(void* objectId)
{
	return {};
}

