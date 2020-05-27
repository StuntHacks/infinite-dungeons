/**
 * @file common/events/TextEvent.hpp
 * @brief Defines the TextEvent-class
 */
#pragma once

#include "common/Event.hpp"

namespace id {
    namespace events {
        /**
         * @brief A text-input event
         */
        class TextEvent: public id::Event {
        public:
            TextEvent(wchar_t character);

            virtual inline std::string getEventName() {
                return "id::events::TextEvent";
            };

            wchar_t getCharacter() const;

        private:
            /* data */
            wchar_t m_character;
        };
    } /* events */
} /* id */
