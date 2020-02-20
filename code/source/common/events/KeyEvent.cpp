#include "common/events/KeyEvent.hpp"

namespace id {
    namespace events {
        KeyEvent::KeyEvent(int keyCode) : m_keyCode(keyCode) { /* do nothing */ }

        int KeyEvent::getKeyCode() {
            return m_keyCode;
        }
    } /* events */
} /* id */
