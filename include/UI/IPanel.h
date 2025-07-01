#pragma once
/**
 * @file UI/IPanel.h
 * @author Noah G. Wood (@NoahGWood)
 * @brief Panel Interface for ImGUI Rendering
 * @version 0.1
 * @date 2025-07-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "Core/Base.h"

class IPanel {
    public:
        virtual ~IPanel() = default;

        virtual const std::string GetName() const = 0; 

        virtual bool OnOpen() { return true; }
        virtual bool OnClose() { return true; }
        virtual bool OnImGuiRender() { return true; }

        virtual bool Undo() { return true; }
        virtual bool Redo() { return true; }

        bool IsOpen = true;
};