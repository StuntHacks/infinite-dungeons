#pragma once

#include <vector>
#include "Drawable.hpp"
#include "Vertex.hpp"
#include "opengl.hpp"

namespace ta {
    namespace graphics {
        /**
         * @brief Can be used to render something without directly displaying it on screen
         */
        class RenderTarget: public Drawable {
        public:
            /**
             * @brief Creates the rendertarget
             */
            RenderTarget(float width, float height);

            /**
             * @brief Destructs the rendertarget
             */
            ~RenderTarget();

            /**
             * @brief Binds the rendertarget
             *
             * This causes all rendering to be redirected to this rendertarget
             */
            void bind();
            void unbind();

            void setPosX(float posX);
            float getPosX();
            void setPosY(float posY);
            float getPosY();
            void setPosition(float posX, float posY);
            void setPosition(ta::graphics::Vector2f dimensions);
            ta::graphics::Vector2f getPosition();

            void draw(ta::graphics::Renderer& renderer, bool);
            GLuint getTexture() const;

        private:
            /* data */
            int m_width, m_height;
            GLuint m_framebuffer, m_texture, m_vao, m_vbo;
            float m_posX, m_posY;
            std::vector<ta::graphics::Vertex> m_vertices;
        };
    } /* graphics */
} /* ta */
