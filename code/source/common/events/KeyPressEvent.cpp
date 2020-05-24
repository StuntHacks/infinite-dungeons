#include "common/events/KeyPressEvent.hpp"

namespace id {
    namespace events {
        KeyPressEvent::KeyPressEvent(int keyCode, State state) :
        m_keyCode(keyCode),
        id::events::PressEvent(state) { /* do nothing */ }

        int KeyPressEvent::getKeyCode() {
            return m_keyCode;
        }
    } /* events */
} /* id */
