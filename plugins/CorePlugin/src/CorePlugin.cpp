#include "CorePlugin.h"

class ProjectBrowserPanel : public IPanel {
public:
    const std::string GetName() const override { return "Project Browser"; }
    bool OnImGuiRender() override {
        if(ImGui::Begin("Project Browser"), &IsOpen){
            ImGui::Text("[Project Files Would Show Here]");
            ImGui::End();
        }
        return true;
    }
};

// Stub example menu
class FileMenu : public IMenu {
public:
    const std::string GetName() const override { return "File"; }
    bool OnImGuiRender() override {
        if (ImGui::MenuItem("Open Project")) {
            // Add project open logic
        }
        if (ImGui::MenuItem("Exit")) {
            // Add shutdown signal
        }
        return true;
    }
};

bool CorePlugin::OnLoad() {
    CORE_INFO("Loading CorePlugin");
    RegisterDefaultPanels();
    RegisterDefaultMenus();
    return true;
}

bool CorePlugin::OnUnload() {
    CORE_INFO("Unloading CorePlugin");
    m_Panels.clear();
    m_Menus.clear();
    return true;
}

void CorePlugin::RegisterDefaultPanels() {
    m_Panels.push_back(std::make_shared<ProjectBrowserPanel>());
}

void CorePlugin::RegisterDefaultMenus() {
    m_Menus.push_back(std::make_shared<FileMenu>());
}
