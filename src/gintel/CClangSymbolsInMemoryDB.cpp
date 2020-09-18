
#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include "CObjectIndex.h"
#include "CObjectStore.h"
#include "CSymbolInfo.h"
#include "CClangSymbolsInMemoryDB.h"
#include "CCamelCaseKeyGenerator.h"
#include "util.h"

using gintel::storage::CSymbolInfo;
using gintel::storage::CObjectStore;
using gintel::storage::CObjectIndex;
using gintel::storage::CClangSymbolsInMemoryDB;
using gintel::modules::CCamelCaseKeyGenerator;

CClangSymbolsInMemoryDB::CClangSymbolsInMemoryDB()
	: m_store(std::make_unique<CObjectStore>()),
	m_index(std::make_unique<CObjectIndex>())
{
}

void CClangSymbolsInMemoryDB::add(std::shared_ptr<CSymbolInfo> symbol)
{
	if (!symbol.use_count())
	{
		throw std::invalid_argument("NULL arguments");
	}

	//	add to store
	auto objectId {m_store->add(symbol)};

	//	generate keys
	auto keys {CCamelCaseKeyGenerator::createKeys(symbol->name())};

	//	add to index
	std::for_each(keys.begin(), keys.end(), [&, this](const std::string& key) {

		if (key.length() >= 3)
		{
			m_index->add(
				gintel::util::string::lowercase(key),
				objectId);
		}
	});
}

std::vector<std::shared_ptr<CSymbolInfo>>
CClangSymbolsInMemoryDB::typeAheadSuggestions(
	const std::string& keyword)
{
	auto resultIds {m_index->typeAheadSuggestions(keyword)};

	std::vector<std::shared_ptr<CSymbolInfo>> result;
	result.reserve(resultIds.size());

	std::for_each(resultIds.begin(), resultIds.end(), [&](const auto& resultId) {
		auto storeObject {m_store->get(resultId)};
		if (storeObject.use_count() > 0)
		{
			result.push_back(std::dynamic_pointer_cast<CSymbolInfo>(storeObject));
		}
	});

	return result;
}

std::vector<std::shared_ptr<CSymbolInfo>> CClangSymbolsInMemoryDB::search(
	const std::string& keyword)
{
	auto lowerKeyword {gintel::util::string::lowercase(keyword)};
	auto resultIds {m_index->search(lowerKeyword)};

	std::vector<std::shared_ptr<CSymbolInfo>> result;
	result.reserve(resultIds.size());

	std::for_each(resultIds.begin(), resultIds.end(), [&](const auto& resultId) {
		auto storeObject {m_store->get(resultId)};
		if (storeObject.use_count() > 0)
		{
			result.push_back(std::dynamic_pointer_cast<CSymbolInfo>(storeObject));
		}
	});

	return result;
}
