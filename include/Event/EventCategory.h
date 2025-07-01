#pragma once
/**
 * @file Event/EventCategory.h
 * @author Noah G. Wood (@NoahGWood)
 * @brief Categories of Events in the VSModEngine
 * @version 0.1
 * @date 2025-07-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */

enum EventCategory {
    None = 0,
    EventCategoryApplication = 1 << 0,
    EventCategoryInput = 1 << 1,
    EventCategoryKeyboard = 1 << 2,
    EventCategoryMouse = 1 << 3,
    EventCategoryEditor = 1 << 4,
};