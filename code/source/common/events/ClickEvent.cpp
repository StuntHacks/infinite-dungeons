#include "common/events/ClickEvent.hpp"

namespace id {
    namespace events {
        ClickEvent::ClickEvent(float posX, float posY) : m_posX(posX), m_posY(posY) { /* do nothing */ }

        float ClickEvent::getPosX() {
            return m_posX;
        }

        float ClickEvent::getPosY() {
            return m_posY;
        }

        id::graphics::Vector2f ClickEvent::getPosition() {
            return { m_posX, m_posY };
        };
    } /* events */
} /* id */
