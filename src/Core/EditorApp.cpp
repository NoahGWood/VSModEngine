#include "Core/EditorApp.h"
#include "VSModEngine.h"
#include <SDL_opengl.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>
#include "CorePlugin/include/CorePlugin.h"
EditorApp::EditorApp()
    : m_MenuManager(std::move(std::make_shared<MenuManager>()))
{    
}

bool EditorApp::Init(){
    CORE_TRACE("Starting Editor App");
    SDL_Init(SDL_INIT_VIDEO);
    m_Window = SDL_CreateWindow("Vintage Story Mod Editor",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    m_GL = SDL_GL_CreateContext(m_Window);
    m_ImContext = ImGui::CreateContext();
    ImGui_ImplSDL2_InitForOpenGL(m_Window, m_GL);
    ImGui_ImplOpenGL3_Init("#version 130");

    m_IO = &ImGui::GetIO();
    m_IO->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    m_IO->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    m_IO->BackendFlags |= ImGuiBackendFlags_PlatformHasViewports;
    m_Running = true;

    // Setup plugins:

    m_PluginManager = std::make_unique<PluginManager>();
    std::shared_ptr<IPlugin> core = std::make_shared<CorePlugin>();
    core->OnLoad();
    m_PluginManager->Register(core);

    for(auto& plugin : m_PluginManager->GetPlugins()){
        for(auto & panel : plugin->GetPanels()){
            RegisterPanel(panel);
        }
        for(auto& menu : plugin->GetMenus()){
            m_MenuManager->AddMenu(menu);
        }
    }

    return true;
}

bool EditorApp::Run(){
    CORE_TRACE("Running Editor App");
    SDL_Event e;
    while(m_Running){
        // SDL poll events
        while(SDL_PollEvent(&e)){
            // Handle closing
            if(e.type == SDL_QUIT){
                m_Running = false;
            } else if(e.type == SDL_WINDOWEVENT){
                // Closing on multi-viewports
                if(e.window.event == SDL_WINDOWEVENT_CLOSE){
                    if(e.window.windowID == SDL_GetWindowID(m_Window)){
                        m_Running = false;
                    }
                }
            }
            // Resizing
            if(e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_RESIZED){
                int newW = e.window.data1;
                int newH = e.window.data2;
                glViewport(0,0, newW, newH);
            }
            // Pass events to ImGui
            ImGui_ImplSDL2_ProcessEvent(&e);
        }
        int fb_width, fb_height;
        SDL_GL_GetDrawableSize(m_Window, &fb_width, &fb_height);
        m_IO->DisplaySize = ImVec2((float)fb_width, (float)fb_height);
        // Start new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        // Render dockspace if enabled
        if(m_IO->ConfigFlags & ImGuiConfigFlags_DockingEnable){
            ImGui::DockSpaceOverViewport();
        }
        // Begin rendering menus
        if(m_MenuManager->HasMenus()){
            if(ImGui::BeginMainMenuBar()){
                m_MenuManager->OnImGuiRender();
                ImGui::EndMainMenuBar();
            }
        }
        // Begin rendering panels
        for(auto& panel : m_Panels){
            if(panel->IsOpen){
                panel->OnImGuiRender();
            }
        }
        // Finalize
        ImGui::Render();
        // Update platform windows
        if(m_IO->ConfigFlags & ImGuiConfigFlags_ViewportsEnable){
            SDL_Window* backup_window = SDL_GL_GetCurrentWindow();
            SDL_GLContext backup_context = SDL_GL_GetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            SDL_GL_MakeCurrent(backup_window, backup_context);
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(m_Window);
        SDL_Delay(16);
    }
    return true;
}

bool EditorApp::Shutdown(){
    CORE_TRACE("Editor App Shutdown");
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
    return true;
}

bool EditorApp::RegisterPanel(std::shared_ptr<IPanel> panel){
    m_Panels.push_back(panel);
    return true;
}