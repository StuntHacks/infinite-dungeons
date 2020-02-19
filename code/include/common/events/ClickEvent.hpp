/**
 * @file common/events/ClickEvent.hpp
 * @brief Defines the ClickEvent-class
 */
#pragma once

#include "common/Event.hpp"
#include "common/graphics/Vertex.hpp"

namespace id {
    namespace events {
        /**
         * @brief A mouseclick on the screen
         */
        class ClickEvent: public id::Event {
        public:
            ClickEvent(float posX, float posY);

            virtual inline std::string getEventName() {
                return "id::ClickEvent";
            };

            float getPosX();

            float getPosY();

            id::graphics::Vector2f getPosition();

        private:
            /* data */
            float m_posX, m_posY;
        };
    } /* events */
} /* id */
