#pragma once
/**
 * @file CorePlugin.h
 * @author Noah G. Wood (@NoahGWood)
 * @brief Core (static) plugin demonstrating how to mod the mod engine
 * @version 0.1
 * @date 2025-07-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "VSModEngine.h"

class CorePlugin : public IPlugin {
public:
    const std::string GetName() const override { return "CorePlugin"; }

    bool OnLoad() override;
    bool OnUnload() override;

private:
    void RegisterDefaultPanels();
    void RegisterDefaultMenus();
};
