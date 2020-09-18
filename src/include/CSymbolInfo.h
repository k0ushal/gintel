#ifndef _CSYMBOL_INFO_H_
#define _CSYMBOL_INFO_H_

#include <string>
#include <filesystem>
#include "IStoreObject.h"

namespace gintel
{
    namespace storage
    {
        enum class SymbolType
        {
            GlobalFunction,
            Class,
            Method
        };

        struct SymbolLocationInfo
        {
            std::filesystem::path file;
        };

        class CSymbolInfo : public IStoreObject
        {
            public:
                CSymbolInfo() = default;
                CSymbolInfo(
                    const std::string& projectName,
                    const std::string& name,
                    SymbolType type,
                    const std::filesystem::path filePath
                    );

            public:
                //  IStoreObject interfaces
                virtual ~CSymbolInfo() = default;
                virtual std::shared_ptr<gintel::storage::IStoreObject> clone() override;
                virtual std::string name() override;

            public:
                bool operator ==(const CSymbolInfo& right) const;

            public:
                std::string m_project;
                std::string m_name;
                SymbolType m_type;
                SymbolLocationInfo m_location;
        };
    }
}

#endif  //  _CSYMBOL_INFO_H_
