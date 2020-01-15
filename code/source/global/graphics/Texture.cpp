#include "global/graphics/Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "extern/stb_image.h"
#include "global/Console.hpp"

namespace id {
    namespace graphics {
        Texture::Texture(bool autoDelete) :
        m_texture(0),
        m_width(0),
        m_height(0),
        m_autoDelete(autoDelete) { /* do nothing */ }

        Texture::Texture(const std::string& filepath, bool smoothTexture, GLenum wrapS, GLenum wrapT, bool autoDelete) :
        m_texture(0),
        m_width(0),
        m_height(0),
        m_autoDelete(autoDelete) {
            loadFromFile(filepath, smoothTexture, wrapS, wrapT);
        }

        Texture::~Texture() {
            if (m_autoDelete) {
                deleteTexture();
            }
        }

        bool Texture::loadFromFile(const std::string& filepath, bool smoothTexture, GLenum wrapS, GLenum wrapT) {
            if (m_texture != 0) {
                return false;
            }

            glGenTextures(1, &m_texture);

            if (!m_texture) {
                return false;
            }

            glBindTexture(GL_TEXTURE_2D, m_texture);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, smoothTexture ? GL_LINEAR : GL_NEAREST);

            int width, height, nrChannels;
            unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);

            if (data) {
                glTexImage2D(GL_TEXTURE_2D, 0, nrChannels < 4 ? GL_RGB : GL_RGBA, width, height, 0, nrChannels < 4 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
                m_width = width;
                m_height = height;

                id::Console::success("Successfully loaded texture \"" + filepath + "\"!", "Texture.cpp:36");
            } else {
                id::Console::error("Failed to load texture \"" + filepath + "\"!", "Texture.cpp:36");
                stbi_image_free(data);
                return false;
            }

            stbi_image_free(data);
            glBindTexture(GL_TEXTURE_2D, 0);

            return true;
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

        bool Texture::getAutoDelete() {
            return m_autoDelete;
        }

        void Texture::setAutoDelete(bool autoDelete) {
            m_autoDelete = autoDelete;
        }

        void Texture::deleteTexture() {
            glDeleteTextures(1, &m_texture);
            m_width = 0;
            m_height = 0;
            m_texture = 0;
        }

        void Texture::bind() {
            glBindTexture(GL_TEXTURE_2D, m_texture);
        }
    } /* graphics */
} /* id */
