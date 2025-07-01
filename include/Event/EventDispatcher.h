#pragma once
/**
 * @file Event/EventDispatcher.h
 * @author Noah G. Wood (@NoahGWood)
 * @brief The event dispatcher handles dispatching events by their type. 
 * @version 0.1
 * @date 2025-07-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "Event/Event.h"

class EventDispatcher{
    public:
        EventDispatcher(Event& event)
            : m_Event(event){}

        template<typename T, typename F>
        bool Dispatch(const F& func){
            if(m_Event.GetType() == T::StaticType()){
                m_Event.Handled = func(static_cast<T&>(m_Event));
                return true;
            }
            return false;
        }
    private:
        Event& m_Event;
};