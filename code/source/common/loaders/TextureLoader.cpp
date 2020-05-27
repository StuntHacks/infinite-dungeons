#include "common/loaders/TextureLoader.hpp"

namespace id {
    namespace loaders {
        TextureLoader::TextureLoader() : m_width(0), m_height(0), m_texture(0) {}

        TextureLoader::~TextureLoader() { unload(); };

        int TextureLoader::getWidth() {
            return m_width;
        }

        int TextureLoader::getHeight() {
            return m_height;
        }

        int TextureLoader::getID() {
            return m_texture;
        }

        void TextureLoader::unload() {
            m_texture = 0;
            m_width = 0;
            m_height = 0;
        };
    } /* loaders */
} /* id */
