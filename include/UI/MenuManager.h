#pragma once
/**
 * @file UI/MenuManager.h
 * @author Noah G. Wood (@NoahGWood)
 * @brief Registers and renders all menus (can be nested in panels if needed).
 * @version 0.1
 * @date 2025-07-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "Core/Base.h"
#include "Core/Logger.h"
#include "UI/IMenu.h"
#include <imgui.h>


class MenuManager {
    public:
        bool HasMenus(){
            return m_Menus.size() > 0;
        }
        bool AddMenu(std::shared_ptr<IMenu> menu){
            if(menu != nullptr){
                m_Menus.push_back(std::move(menu));
                return true;
            } else {
                CORE_WARN("MenuManager::AddMenu was passed a nullptr");
            }
            return false;
        }
        bool OnImGuiRender() {
            try{
                for(auto& menu : m_Menus) {
                    if(ImGui::BeginMenu(menu->GetName().c_str())){
                        menu->OnImGuiRender();
                        for(auto& sub : menu->GetSubMenus()){
                            RenderMenuRecursive(sub);
                        }
                        ImGui::EndMenu();
                    }
                }
            } catch (const std::exception& e){
                CORE_ERROR("Exception in MenuManager::OnImGuiRender: ", e.what());
                return false;
            }
            return true;
        }

        bool RenderMenuRecursive(const std::shared_ptr<IMenu>& menu){
            if(!menu){
                CORE_WARN("MenuManager::RenderMenuRecursive was passed a nullptr");
                return false;
            }
            try {
                if(ImGui::BeginMenu(menu->GetName().c_str())){
                    if(!menu->OnImGuiRender()) return false;
                    for(auto& sub : menu->GetSubMenus()){
                        RenderMenuRecursive(sub);
                    }
                    ImGui::EndMenu();
                }
            } catch(const std::exception& e){
                CORE_ERROR("Exception in MenuManager::RenderMenuRecursive: ", e.what());
                return false;
            }
            return true;
        }

    private:
        std::vector<std::shared_ptr<IMenu>> m_Menus;
};