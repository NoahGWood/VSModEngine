#pragma once
/**
 * @file Core/EditorApp.h
 * @author Noah G. Wood (@NoahGWood)
 * @brief EditorApp handles the full engine lifecycle.
 * @version 0.1
 * @date 2025-07-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <SDL.h>
#include <imgui.h>
#include "Plugin/PluginManager.h"
#include "Core/Base.h"
#include "UI/IPanel.h"
#include "UI/MenuManager.h"

class EditorApp {
    public:
        EditorApp();
        bool Init();
        bool Run();
        bool Shutdown();

        bool RegisterPanel(std::shared_ptr<IPanel> panel);
        std::shared_ptr<MenuManager> GetMenuManager();

    private:
        bool m_Running = true;
        std::shared_ptr<PluginManager> m_PluginManager;
        std::vector<std::shared_ptr<IPanel>> m_Panels;
        std::shared_ptr<MenuManager> m_MenuManager;
        ImGuiIO* m_IO;
        ImGuiContext* m_ImContext;
        SDL_Window* m_Window;
        SDL_GLContext m_GL;
};