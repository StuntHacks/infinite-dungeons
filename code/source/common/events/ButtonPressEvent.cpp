#include "common/events/ButtonPressEvent.hpp"

namespace id {
    namespace events {
        ButtonPressEvent::ButtonPressEvent(int button, State state) :
        m_button(button),
        id::events::PressEvent(state) { /* do nothing */ }

        int ButtonPressEvent::getButton() {
            return m_button;
        }
    } /* events */
} /* id */
