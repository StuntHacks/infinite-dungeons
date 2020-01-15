#pragma once

#include <string>
#include <algorithm>
#include "opengl.hpp"

namespace id {
    namespace graphics {
        class Texture {
        public:
            Texture(bool autoDelete = true);
            Texture(const std::string& filepath, bool smoothTexture = true, GLenum wrapS = GL_REPEAT, GLenum wrapT = GL_REPEAT, bool autoDelete = true);
            virtual ~Texture();

            bool loadFromFile(const std::string& filepath, bool smoothTexture = true, GLenum wrapS = GL_REPEAT, GLenum wrapT = GL_REPEAT);

            unsigned int getTexture();
            unsigned int getWidth();
            unsigned int getHeight();

            bool getAutoDelete();
            void setAutoDelete(bool autoDelete);
            void deleteTexture();

            void bind();

        private:
            /* data */
            unsigned int m_texture, m_width, m_height;
            bool m_autoDelete;
        };
    } /* graphics */
} /* id */
