#pragma once

#include "global/graphics/Color.hpp"
#include "global/graphics/Drawable.hpp"
#include "global/graphics/ShaderProgram.hpp"
#include "global/graphics/Texture.hpp"
#include "global/graphics/Vertex.hpp"

#include <vector>

namespace ta {
    namespace graphics {
        class Sprite: public Drawable {
        public:
            Sprite();

            void setTexture(ta::graphics::Texture& texture);
            ta::graphics::Texture& getTexture();

            void setWidth(float width);
            float getWidth();
            void setHeight(float height);
            float getHeight();
            void setDimensions(float width, float height);
            void setDimensions(ta::graphics::Vector2f dimensions);
            ta::graphics::Vector2f getDimensions();

            void setPositionX(float posX);
            void moveX(float delta);
            float getPositionX();
            void setPositionY(float posY);
            void moveY(float delta);
            float getPositionY();
            void setPosition(float posX, float posY);
            void setPosition(ta::graphics::Vector2f position);
            void move(float deltaX, float deltaY);
            ta::graphics::Vector2f getPosition();

            void setRotation(float rotation);
            void rotate(float delta);
            float getRotation();

            void setOpacity(float opacity);
            float getOpacity();

            void setColor(ta::graphics::Color color);
            ta::graphics::Color getColor();

            void setShader(ta::graphics::ShaderProgram& shader);
            ta::graphics::ShaderProgram& getShader();

            virtual void draw(ta::graphics::Renderer& renderer, bool);

        private:
            /* data */
            unsigned int m_vao, m_vbo;
            float m_posX, m_posY, m_width, m_height, m_rotation, m_opacity;
            ta::graphics::Color m_color;
            std::vector<ta::graphics::Vertex> m_vertices;
            ta::graphics::Texture m_texture;
            ta::graphics::ShaderProgram m_shader;
        };
    } /* graphics */
} /* ta */
