#include "common/loaders/implementations/ImageLoader.hpp"
#include "common/Console.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "extern/stb_image.h"

namespace id {
    namespace loaders {
        bool ImageLoader::loadFromFile(const std::string& filepath) {
            int width, height, nrChannels;
            unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);

            if (_load(data, width, height, nrChannels)) {
                id::Console::success("Successfully loaded texture \"" + filepath + "\"!", "ImageLoader.cpp:12");

                stbi_image_free(data);
                return true;
            }

            id::Console::error("Failed to load texture \"" + filepath + "\"!", "ImageLoader.cpp:12");

            stbi_image_free(data);
            return false;
        }

        bool ImageLoader::loadFromMemory(const std::string& buffer) {
            int width, height, nrChannels;
            unsigned char* data = stbi_load_from_memory(reinterpret_cast<const unsigned char*>(buffer.c_str()), buffer.length(), &width, &height, &nrChannels, 0);

            if (_load(data, width, height, nrChannels)) {
                id::Console::success("Successfully loaded texture from buffer!", "ImageLoader.cpp:29");

                stbi_image_free(data);
                return true;
            }

            id::Console::error("Failed to load texture from buffer!", "ImageLoader.cpp:29");

            stbi_image_free(data);
            return false;
        }

        // private methods
        bool ImageLoader::_load(unsigned char* data, int width, int height, int nrChannels) {
            if (m_texture != 0) {
                return false;
            }

            glGenTextures(1, &m_texture);

            if (!m_texture) {
                return false;
            }

            glBindTexture(GL_TEXTURE_2D, m_texture);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            if (data) {
                glTexImage2D(GL_TEXTURE_2D, 0, nrChannels < 4 ? GL_RGB : GL_RGBA, width, height, 0, nrChannels < 4 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
                m_width = width;
                m_height = height;
            } else {
                return false;
            }

            glBindTexture(GL_TEXTURE_2D, 0);
            return true;
        }
    } /* loaders */
} /* id */
