
#include "CSymbolInfo.h"
#include "IStoreObject.h"

using gintel::storage::CSymbolInfo;
using gintel::storage::SymbolType;

CSymbolInfo::CSymbolInfo(
    const std::string& projectName,
    const std::string& name,
    SymbolType type,
    const std::string& filePath
    ) : m_project{projectName}, m_name{name},
        m_type{type}, m_location{filePath}
{
}

bool CSymbolInfo::operator ==(const CSymbolInfo& right) const
{
    return (m_project == right.m_project &&
            m_name == right.m_name &&
            m_type == right.m_type &&
            m_location.file == right.m_location.file);
}

std::shared_ptr<gintel::storage::IStoreObject> CSymbolInfo::clone()
{
    auto obCopy {std::make_shared<CSymbolInfo>()};
    obCopy->m_project = this->m_project;
    obCopy->m_name = this->m_name;
    obCopy->m_type = this->m_type;
    obCopy->m_location = this->m_location;

    return obCopy;
}

std::string CSymbolInfo::name()
{
    return m_name;
}
