#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include <string>

namespace ta {
    namespace graphics {
        class Font {
        public:
            Font(const std::string& filename = "");
            virtual ~Font();

            bool loadFromFile(const std::string& filename);
            bool loadFromMemory(const unsigned char* location, signed long size, signed long index = 0);

            FT_Face& getFontFace();

        private:
            /* data */
            std::string m_path;
            FT_Library m_freetype;
            FT_Face m_face;
        };
    } /* graphics */
} /* ta */
