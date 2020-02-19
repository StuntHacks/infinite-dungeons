/**
 * @file common/Event.hpp
 * @brief Defines the Event and EventData-classes
 */
#pragma once

#include <string>

namespace id {
    /**
     * @brief The base class for all Events
     */
    class Event {
    public:
        /**
         * @brief Default constructor
         */
        Event();

        /**
         * @brief Destructor
         */
        virtual ~Event() { /* do nothing */ }

        /**
         * @brief Stops the Event from propagating further, unless `Event::forcePropagation()` was called before
         * @return Whether the event was successfully stopped or not (usually only false when the Event was forced to propagate)
         */
        virtual bool stopPropagation();

        /**
         * @brief Forces the Event to propagate and prevents it from being stopped
         */
        virtual void forcePropagation();

        /**
         * @brief Returns whether the Event is currently propagating
         * @return `true` if the Event is currently propagating, false otherwise
         */
        virtual bool isPropagating();

        /**
         * @brief Returns whether the Event is forced to propagate
         * @return `true` if the Event is forced to propagate, false otherwise
         */
        virtual bool isForced();

        /**
         * @brief Returns the name of the Event as a string. Implement this in your child-Events
         * @return The name of the triggered Event as a string
         */
        virtual inline std::string getEventName() = 0;
    private:
        /* data */
        bool m_propagating, m_forced;
    };
} /* id */
