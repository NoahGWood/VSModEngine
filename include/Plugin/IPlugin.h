#pragma once
/**
 * @file Plugin/IPlugin.h
 * @author Noah G. Wood (@NoahGWood)
 * @brief The Plugin Interface Class. Inherit from this in your plugins.
 * @version 0.1
 * @date 2025-07-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "Core/Base.h"
class IPanel;   // Forward declared
class IMenu;    // Forward declared

class IPlugin{
    public:
        virtual ~IPlugin() = default;
        virtual const std::string GetName() const = 0;
        // Called once at load
        virtual bool OnLoad() { return true; }
        // Called on shutdown
        virtual bool OnUnload() { return true; }
        virtual bool OnUpdate() { return true; }
        virtual bool OnImGuiRender() { return true; }
        virtual bool OnEvent() { return true; }
        virtual const std::vector<std::shared_ptr<IPanel>>& GetPanels() const { return m_Panels; }
        virtual const std::vector<std::shared_ptr<IMenu>>& GetMenus() const { return m_Menus; }

    protected:
        std::vector<std::shared_ptr<IPanel>> m_Panels;
        std::vector<std::shared_ptr<IMenu>> m_Menus;
};