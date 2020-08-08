
#include <memory>
#include <vector>
#include <string>
#include "CSymbolsDB.h"

using gintel::storage::CSymbolsDB;


void CSymbolsDB::add(std::shared_ptr<IStoreObject> symbol)
{
	//	add to store
	//	add to index
}

std::vector<std::shared_ptr<IStoreObject>> CSymbolsDB::search(std::string keyword)
{
}

