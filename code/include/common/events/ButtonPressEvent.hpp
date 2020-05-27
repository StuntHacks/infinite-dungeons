/**
 * @file common/events/ButtonPressEvent.hpp
 * @brief Defines the ButtonPressEvent-class
 */
#pragma once

#include "common/events/PressEvent.hpp"

namespace id {
    namespace events {
        /**
         * @brief A button-press
         */
        class ButtonPressEvent: public id::events::PressEvent {
        public:
            ButtonPressEvent(int button, PressEvent::State state);

            virtual inline std::string getEventName() {
                return "id::events::ButtonPressEvent";
            };

            int getButton();

        private:
            /* data */
            int m_button;
        };
    } /* events */
} /* id */
