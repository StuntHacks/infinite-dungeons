#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H
#include <string>
#include <map>

#include "opengl.hpp"
#include "switch/mutex.hpp"

namespace ta {
    namespace graphics {
        class Font {
        public:
            struct Character {
                bool       valid;
                GLuint     texture; // ID handle of the glyph texture
                glm::ivec2 size;    // Size of glyph
                glm::ivec2 bearing; // Offset from baseline to left/top of glyph
                GLuint     advance; // Offset to advance to next glyph
            };

            Font(const std::string& filename = "");
            virtual ~Font();

            bool loadFromFile(const std::string& filename);
            bool loadFromMemory(const unsigned char* location, signed long size, signed long index = 0);

            FT_Face& getFontFace();
            ta::graphics::Font::Character getCharacter(wchar_t character, int height);

        private:
            /* data */
            std::string m_path;
            std::map<FT_ULong, std::map<FT_ULong, ta::graphics::Font::Character>> m_characters;

            ta::Mutex m_mutex;
            FT_Library m_freetype;
            FT_Face m_face;
        };
    } /* graphics */
} /* ta */
