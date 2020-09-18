
#include <vector>
#include <string>
#include <any>
#include "CObjectIndex.h"

using gintel::storage::CObjectIndex;

void CObjectIndex::add(const std::string& key, std::any value)
{
    if (key.empty())
    {
        throw std::invalid_argument("Empty key");
    }
    
    auto result{m_index.emplace(key, std::vector<std::any>{})};
    result.first->second.push_back(value);
}

std::vector<std::any> CObjectIndex::search(const std::string& key)
{
    auto itr {m_index.find(key)};
    if (itr == m_index.end())
    {
        return {};
    }

    return itr->second;
}

std::vector<std::any> CObjectIndex::typeAheadSuggestions(const std::string& key)
{
    return {};
}
