#pragma once

#include <string>
#include "opengl.hpp"

namespace ta {
    namespace graphics {
        class Texture {
        public:
            Texture();
            virtual ~Texture();

            bool loadFromFile(const std::string& filepath, bool smoothTexture = true, GLenum wrapS = GL_REPEAT, GLenum wrapT = GL_REPEAT);

            unsigned int getTexture();
            unsigned int getWidth();
            unsigned int getHeight();

        private:
            /* data */
            unsigned int m_texture, m_width, m_height;
        };
    } /* graphics */
} /* ta */
