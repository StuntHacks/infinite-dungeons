#include "common/events/InputEvent.hpp"

namespace id {
    namespace events {
        InputEvent::InputEvent(const std::string& inputName, State state) :
        id::events::PressEvent(state),
        m_name(inputName) { /* do nothing */ }
    } /* events */
} /* id */
