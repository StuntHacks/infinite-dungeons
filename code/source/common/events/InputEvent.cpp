#include "common/events/InputEvent.hpp"

namespace id {
    namespace events {
        InputEvent::InputEvent(const std::string& inputName, int keyCode) :
        id::events::KeyEvent(keyCode),
        m_name(inputName) { /* do nothing */ }
    } /* events */
} /* id */
