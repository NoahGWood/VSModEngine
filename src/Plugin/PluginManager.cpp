#include "Plugin/PluginManager.h"
#include "VSModEngine.h"

using CreatePluginFn = IPlugin* (*)();

bool PluginManager::LoadPlugin(const std::string& path){
    if(!Utils::FS::path_exists(path)){
        CORE_WARN("Plugin file not found: {}", path);
        return false;
    }
#ifdef _WIN32
    PluginHandle handle = LoadLibraryA(path.c_str());
    if(!handle){
        CORE_ERROR("Failed to load plugin: {}", path);
        return false;
    }
    auto createFn = (CreatePluginFn)GetProcAddress(handle, "CreatePlugin");
#else
    PluginHandle handle = dlopen(path.c_str(), RTLD_LAZY);
    if(!handle){
        CORE_ERROR("Failed to load plugin: {}", path);
        return false;
    }
    auto createFn = (CreatePluginFn)dlsym(handle, "CreatePlugin");
#endif
    if(!createFn){
        CORE_ERROR("CreatePlugin function not found in: {}", path);
#ifdef _WIN32
        FreeLibrary(handle);
#else
        dlclose(handle);
#endif
        return false;
    }

    std::shared_ptr<IPlugin> plugin(createFn());
    if(!plugin){
        CORE_ERROR("CreatePlugin returned null for: {}", path);
#ifdef _WIN32
        FreeLibrary(handle);
#else
        dlclose(handle);
#endif
        return false;
    }
    try{
        assert(plugin->OnLoad() == true);
    } catch(const std::exception& e){
        CORE_ERROR("Plugin {} failed to load properly: {}", path, e.what());
#ifdef _WIN32
        FreeLibrary(handle);
#else
        dlclose(handle);
#endif
        return false;
    }
    return true;
}

bool PluginManager::UnloadAll(){
    bool all_success = true;
    for(auto& plugin: m_Plugins){
        try{
            assert(plugin->OnUnload()==true);
        } catch(const std::exception& e){
            CORE_ERROR("Plugin failed to unload correctly: {}", e.what());
            all_success = false;
        }
    }
    m_Plugins.clear();
    for(auto& [name, handle] : m_Handles){
#ifdef _WIN32
        FreeLibrary(handle);
#else
        dlclose(handle);
#endif
        CORE_INFO("Unloaded plugin: {}", name);
    }
    m_Handles.clear();
    return all_success;
}

bool PluginManager::Register(std::shared_ptr<IPlugin> plugin) {
    if (plugin) {
        CORE_INFO("Registering plugin: {}", plugin->GetName());
        m_Plugins.push_back(std::move(plugin));
        return true;
    }
    CORE_ERROR("PluginManager::Register was handed a nullptr!");
    return false;
}
