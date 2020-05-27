#include "common/events/TextEvent.hpp"

namespace id {
    namespace events {
        TextEvent::TextEvent(wchar_t character) :
        m_character(character) { /* do nothing */ }

        wchar_t TextEvent::getCharacter() const {
            return m_character;
        }
    } /* events */
} /* id */
