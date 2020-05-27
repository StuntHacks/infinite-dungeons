/**
 * @file common/events/KeyPressEvent.hpp
 * @brief Defines the KeyPressEvent-class
 */
#pragma once

#include "common/events/PressEvent.hpp"

namespace id {
    namespace events {
        /**
         * @brief A key-press
         */
        class KeyPressEvent: public id::events::PressEvent {
        public:
            KeyPressEvent(int keyCode, PressEvent::State state);

            virtual inline std::string getEventName() {
                return "id::events::KeyPressEvent";
            };

            int getKeyCode();

        private:
            /* data */
            int m_keyCode;
        };
    } /* events */
} /* id */
