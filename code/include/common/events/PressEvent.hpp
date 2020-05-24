/**
 * @file common/events/PressEvent.hpp
 * @brief Defines the PressEvent-class
 */
#pragma once

#include "common/Event.hpp"

namespace id {
    namespace events {
        /**
         * @brief An arbitrary press
         */
        class PressEvent: public id::Event {
        public:
            enum class State: int {
                Release = 0,
                Press,
                Repeat
            };

            PressEvent(State state);

            virtual inline std::string getEventName() {
                return "id::events::PressEvent";
            };

            State getState();

        private:
            /* data */
            State m_state;
        };
    } /* events */
} /* id */
