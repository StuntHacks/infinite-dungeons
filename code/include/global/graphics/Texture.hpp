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

        private:
            /* data */
            unsigned int m_texture;
        };
    } /* graphics */
} /* ta */
