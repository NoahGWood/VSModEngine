#pragma once
/**
 * @file Event/Event.h
 * @author Noah G. Wood (@NoahGWood)
 * @brief Base Event Class
 * @version 0.1
 * @date 2025-07-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "Core/Base.h"
#include "Event/EventCategory.h"
#include "Event/EventType.h"

class Event {
    public:
        virtual ~Event() = default;
        virtual EventType GetType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;

        bool InCategory(EventCategory category) const {
            return GetCategoryFlags() & category;
        }

        bool handled = false;
}