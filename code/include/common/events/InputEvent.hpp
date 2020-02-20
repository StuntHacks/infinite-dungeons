/**
 * @file common/events InputEvent.hpp
 * @brief Defines the InputEvent-class
 */
#pragma once

#include "common/events/KeyEvent.hpp"
#include "common/graphics/Vertex.hpp"

namespace id {
    namespace events {
        /**
         * @brief An input registered by the InputManager
         */
        class InputEvent: public id::events::KeyEvent {
        public:
            InputEvent(const std::string& inputName, int keyCode);

            inline std::string getEventName() {
                return m_name;
            };

        private:
            /* data */
            std::string m_name;
        };
    } /* events */
} /* id */
