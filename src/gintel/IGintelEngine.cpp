#include "IGintelEngine.h"
#include "CGintelEngine.h"

using gintel::modules::IGintelEngine;
using gintel::modules::CGintelEngine;

std::shared_ptr<IGintelEngine> g_gintelInstance;

std::shared_ptr<IGintelEngine> IGintelEngine::getInstance()
{
    if (g_gintelInstance.use_count() > 0)
    {
        return g_gintelInstance;
    }

    auto instance {std::make_shared<CGintelEngine>()};
    g_gintelInstance = std::dynamic_pointer_cast<IGintelEngine>(instance);
    return g_gintelInstance;
}

//  C style exports for dynamically linked apps
gintel::modules::IGintelEngine* createGintelInstance()
{
    return new CGintelEngine();
}

void destroyGintelInstance(gintel::modules::IGintelEngine* pInstance)
{
    if (!pInstance)
        return;

    delete pInstance;
}
