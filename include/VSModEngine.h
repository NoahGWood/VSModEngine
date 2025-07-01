#pragma once
/**
 * @file VSModEngine.h
 * @author Noah G. Wood (@NoahGWood)
 * @brief Simplified Include Header for the VSModEngine
 * @version 0.1
 * @date 2025-07-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "Core/Base.h"
#include "Core/Logger.h"
// #include "Core/EditorApp.h" // Don't include in external plugins

#include "Utils/fs.h"

#include "Plugin/IPlugin.h"
#include "Plugin/PluginManager.h"

#include "UI/IMenu.h"
#include "UI/IPanel.h"
#include "UI/MenuManager.h" 
#include <imgui.h>