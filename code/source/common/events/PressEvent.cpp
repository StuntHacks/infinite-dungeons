#include "common/events/PressEvent.hpp"

namespace id {
    namespace events {
        PressEvent::PressEvent(State state) :
        m_state(state) { /* do nothing */ }

        PressEvent::State PressEvent::getState() {
            return m_state;
        }
    } /* events */
} /* id */
