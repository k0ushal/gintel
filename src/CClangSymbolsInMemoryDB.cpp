
#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include "CClangParser.h"
#include "CClangSymbolsInMemoryDB.h"
#include "CObjectIndex.h"

using gintel::storage::CClangSymbolsInMemoryDB;
using gintel::modules::CClangParser;

void CClangSymbolsInMemoryDB::add(std::shared_ptr<IStoreObject> symbol)
{
	//	add to store
	auto objectId {m_store.add(symbol)};

	//	[TODO] generate different keys for symbol here.
	//	required for type-ahead suggestions

	//	add to index
	m_index.add(symbol->name(), objectId);
}

std::vector<std::shared_ptr<CClangParser::CObjectInfo>> CClangSymbolsInMemoryDB::typeAheadSuggestions(
	const std::string& keyword)
{
	auto resultIds {m_index.typeAheadSuggestions(keyword)};

	std::vector<std::shared_ptr<CClangParser::CObjectInfo>> result;
	result.reserve(resultIds.size());

	std::for_each(resultIds.begin(), resultIds.end(), [&](const auto& resultId) {
		auto storeObject {m_store.get(resultId)};
		if (storeObject.use_count() > 0)
		{
			result.push_back(std::dynamic_pointer_cast<CClangParser::CObjectInfo>(storeObject));
		}
	});

	return result;
}

std::vector<std::shared_ptr<CClangParser::CObjectInfo>> CClangSymbolsInMemoryDB::search(
	const std::string& keyword)
{
	auto resultIds {m_index.search(keyword)};

	std::vector<std::shared_ptr<CClangParser::CObjectInfo>> result;
	result.reserve(resultIds.size());

	std::for_each(resultIds.begin(), resultIds.end(), [&](const auto& resultId) {
		auto storeObject {m_store.get(resultId)};
		if (storeObject.use_count() > 0)
		{
			result.push_back(std::dynamic_pointer_cast<CClangParser::CObjectInfo>(storeObject));
		}
	});

	return result;
}
