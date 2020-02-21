/**
 * @file common/EventDispatcher.hpp
 * @brief Defines the EventDispatcher-class
 */
#pragma once

#include <functional>
#include <map>

#include "TypedEventDispatcher.hpp"

namespace id {
    /**
     * @brief Implementes id::TypedEventDispatcher with id::Event.
     *
     * This allows for multiple types of events to be dispatched with the same dispatcher.
     * @note You need to `dynamic_cast` the passed Event to the Event-implementation needed inside all callback-functions in order to access it's data
     */
    class EventDispatcher: public id::TypedEventDispatcher<id::Event> {};
} /* id */
