#include "common/Event.hpp"

namespace id {
    Event::Event() : m_propagating(true), m_forced(false) { /* do nothing */ }

    bool Event::stopPropagation() {
        if (!m_forced) {
            m_propagating = false;
            return true;
        }

        return false;
    }

    void Event::forcePropagation() {
        m_forced = true;
    }

    bool Event::isPropagating() {
        return m_propagating;
    }

    bool Event::isForced() {
        return m_forced;
    }
} /* id */
