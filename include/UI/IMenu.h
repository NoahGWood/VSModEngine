#pragma once
/**
 * @file UI/IMenu.h
 * @author Noah G. Wood (@NoahGWood)
 * @brief Menu Interface for ImGUI Rendering
 * @version 0.1
 * @date 2025-07-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "Core/Base.h"

class IMenu {
    public:
        virtual ~IMenu() = default;
        
        virtual const std::string GetName() const = 0; 

        virtual bool OnImGuiRender() { return true; }

        virtual std::vector<std::shared_ptr<IMenu>> GetSubMenus() { return {}; }
};