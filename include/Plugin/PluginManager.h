#pragma once
/**
 * @file Plugin/PluginManager.h
 * @author Noah G. Wood (@NoahGWood)
 * @brief Handles loading, initializing, and unloading plugins for VSModEngine
 * @version 0.1
 * @date 2025-07-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "Core/Base.h"
#include "Plugin/IPlugin.h"

#ifdef _WIN32
    #include <Windows.h>
    using PluginHandle = HMODULE;
#else
    #include <dlfcn.h>
    using PluginHandle = void*;
#endif

struct PluginEntry {
    std::shared_ptr<IPlugin> instance;
    PluginHandle handle;
};

class PluginManager{
    public:
        // PluginManager();
        ~PluginManager() { UnloadAll(); }
        
        bool Register(std::shared_ptr<IPlugin> plugin);
        bool LoadPlugin(const std::string& path);
        bool UnloadAll();
        const std::vector<std::shared_ptr<IPlugin>>& GetPlugins() const { return m_Plugins; }

    private:
        std::vector<std::shared_ptr<IPlugin>> m_Plugins;
        std::unordered_map<std::string, PluginHandle> m_Handles;
};