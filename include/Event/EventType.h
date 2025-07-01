#pragma once
/**
 * @file Event/EventType.h
 * @author Noah G. Wood (@NoahGWood)
 * @brief Types of Events in the VSModEngine
 * @version 0.1
 * @date 2025-07-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */

// Needs work, ngl, didn't even try:
enum class EventType{
    NONE = 0,
    WindowResized,
    FileDropped,
    ProjectOpened,
    Custom
};