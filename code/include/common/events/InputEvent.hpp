/**
 * @file common/events InputEvent.hpp
 * @brief Defines the InputEvent-class
 */
#pragma once

#include "common/events/PressEvent.hpp"

namespace id {
    namespace events {
        /**
         * @brief A named input registered by the InputManager, representing a key-press
         */
        class InputEvent: public id::events::PressEvent {
        public:
            InputEvent(const std::string& inputName, PressEvent::State state);

            virtual inline std::string getEventName() {
                return m_name;
            };

        private:
            /* data */
            std::string m_name;
        };
    } /* events */
} /* id */
