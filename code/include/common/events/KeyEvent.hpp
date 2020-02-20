/**
 * @file common/events/KeyEvent.hpp
 * @brief Defines the KeyEvent-class
 */
#pragma once

#include "common/Event.hpp"
#include "common/graphics/Vertex.hpp"

namespace id {
    namespace events {
        /**
         * @brief A key-press
         */
        class KeyEvent: public id::Event {
        public:
            KeyEvent(int keyCode);

            virtual inline std::string getEventName() {
                return "id::KeyEvent";
            };

            int getKeyCode();

        private:
            /* data */
            int m_keyCode;
        };
    } /* events */
} /* id */
