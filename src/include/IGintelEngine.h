#ifndef _IGINTEL_ENGINE_H_
#define _IGINTEL_ENGINE_H_

#include <vector>
#include <string>
#include "CSymbolInfo.h"

namespace gintel
{
    namespace modules
    { 
        struct SourceProject
        {
            std::string projectName;
            std::string srcDirPath;
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

/*************************************************
 * E X P O R T S
 ************************************************/

extern "C"
{
    gintel::modules::IGintelEngine* createGintelInstance();
    void destroyGintelInstance(gintel::modules::IGintelEngine*);
}

/*************************************************
 * T Y P E D E F S
 ************************************************/

typedef gintel::modules::IGintelEngine* (*pfn_createGintelInstance)();
typedef void (*pfn_destroyGintelInstance)(gintel::modules::IGintelEngine*);


#endif  //  _IGINTEL_ENGINE_H_
