#include "common/events/KeyPressEvent.hpp"

namespace id {
    namespace events {
        KeyPressEvent::KeyPressEvent(int keyCode, State state) :
        id::events::PressEvent(state),
        m_keyCode(keyCode) { /* do nothing */ }

        int KeyPressEvent::getKeyCode() {
            return m_keyCode;
        }
    } /* events */
} /* id */
