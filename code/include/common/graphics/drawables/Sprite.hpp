#pragma once

#include "common/Asset.hpp"
#include "common/graphics/Color.hpp"
#include "common/graphics/Drawable.hpp"
#include "common/graphics/ShaderProgram.hpp"
#include "common/graphics/Texture.hpp"
#include "common/graphics/Vertex.hpp"

#include <vector>

namespace id {
    namespace graphics {
        class Sprite: public Drawable {
        public:
            Sprite();
            virtual ~Sprite();

            void setTexture(id::graphics::Texture& texture);
            void setTexture(const std::string& assetpath, bool smoothTexture = true);
            void setTexture(id::Asset asset, bool smoothTexture = true);
            id::graphics::Texture& getTexture();

            void setWidth(float width);
            float getWidth();
            void setHeight(float height);
            float getHeight();
            void setDimensions(float width, float height);
            void setDimensions(id::graphics::Vector2f dimensions);
            id::graphics::Vector2f getDimensions();

            void setPositionX(float posX);
            void moveX(float delta);
            float getPositionX();
            void setPositionY(float posY);
            void moveY(float delta);
            float getPositionY();
            void setPosition(float posX, float posY);
            void setPosition(id::graphics::Vector2f position);
            void move(float deltaX, float deltaY);
            id::graphics::Vector2f getPosition();

            void setRotation(float rotation);
            void rotate(float delta);
            float getRotation();

            void setOpacity(float opacity);
            float getOpacity();

            void setColor(id::graphics::Color color);
            id::graphics::Color getColor();

            void setShader(id::graphics::ShaderProgram& shader);
            id::graphics::ShaderProgram& getShader();

            virtual void draw(id::graphics::Renderer& renderer, bool);

        private:
            /* data */
            unsigned int m_vao, m_vbo;
            float m_posX, m_posY, m_width, m_height, m_rotation, m_opacity;
            id::graphics::Color m_color;
            std::vector<id::graphics::Vertex> m_vertices;
            id::graphics::Texture m_texture;
            id::graphics::ShaderProgram m_shader;
        };
    } /* graphics */
} /* id */
