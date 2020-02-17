/**
 * @file common/Event.hpp
 * @brief Defines the Event-class
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
         * @brief The base class for all EventData-packets
         *
         * You should always
         */
        class EventData {
        public:
            /**
             * @brief Returns the name of the Event as a string. Implement this in the EventData-packets of your child-events
             * @return The name of the triggered Event as a string
             */
            virtual std::string getEventName() = 0;
        };

        virtual ~Event() { /* do nothing */ }

        virtual void trigger();
        virtual bool stopPropagation();
        virtual void forcePropagation();
        virtual bool isPropagating();
        virtual bool isForced();

        virtual EventData& getData() = 0;
    private:
        /* data */
        bool m_propagating, m_forced;
    };
} /* id */
