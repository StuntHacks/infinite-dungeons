#include "common/graphics/Texture.hpp"
#include "common/Console.hpp"

namespace id {
    namespace graphics {
        Texture::Texture(bool autoDelete) :
        m_texture(0),
        m_width(0),
        m_height(0) {
            setAutoDelete(autoDelete);
        }

        Texture::~Texture() {
            if (m_autoDelete) {
                deleteThis();
            }
        }

        bool Texture::isLoaded() {
            return m_texture;
        }

        unsigned int Texture::getTexture() {
            return m_texture;
        }

        unsigned int Texture::getWidth() {
            return m_width;
        }

        unsigned int Texture::getHeight() {
            return m_height;
        }

        void Texture::deleteThis() {
            if (isLoaded()) {
                glDeleteTextures(1, &m_texture);
            }

            m_width = 0;
            m_height = 0;
            m_texture = 0;
        }

        void Texture::bind() {
            if (isLoaded()) {
                glBindTexture(GL_TEXTURE_2D, m_texture);
            }
        }
    } /* graphics */
} /* id */
