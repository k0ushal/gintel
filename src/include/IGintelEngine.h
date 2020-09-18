#ifndef _IGINTEL_ENGINE_H_
#define _IGINTEL_ENGINE_H_

#include <vector>
#include <string>
#include <filesystem>

namespace gintel
{
    namespace storage
    {
        class CSymbolInfo;
    }

    namespace modules
    { 
        struct SourceProject
        {
            std::string projectName;
            std::filesystem::path srcDirPath;
        };
        
        class IGintelEngine
        {
            public:
                virtual ~IGintelEngine() = default;
                virtual void addProject(const SourceProject &project) = 0;
                virtual void rebuildSymbolsDB() = 0;
                virtual std::vector<std::shared_ptr<gintel::storage::CSymbolInfo>> searchSymbol(
                    const std::string &keyword) = 0;

            public:
                static std::shared_ptr<IGintelEngine> getInstance();
        };
    }
}

#endif  //  _IGINTEL_ENGINE_H_
