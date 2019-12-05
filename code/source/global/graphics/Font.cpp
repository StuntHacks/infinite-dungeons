#include "global/graphics/Font.hpp"
#include "global/Console.hpp"

namespace ta {
    namespace graphics {
        Font::Font(const std::string& filename) :
        m_path(filename),
        m_face(nullptr) {
            if (FT_Init_FreeType(&m_freetype)) {
                ta::Console::error("FREETYPE: Could not init FreeType Library", "Font.cpp:9");
                return;
            }

            ta::Console::success("FREETYPE: Successfully loaded FreeType Library", "Font.cpp:9");

            if (filename != "") {
                loadFromFile(filename);
            }
        }

        Font::~Font() {
            if (m_face != nullptr) {
                FT_Done_Face(m_face);
            }

            FT_Done_FreeType(m_freetype);
        }

        bool Font::loadFromFile(const std::string& filename) {
            if (m_face != nullptr) {
                FT_Done_Face(m_face);
                m_face = nullptr;
            }

            int error = FT_New_Face(m_freetype, filename.c_str(), 0, &m_face);

            if (error != 0) {
                ta::Console::error("FREETYPE: Failed to load font from file. error: " + std::to_string(error), "Font.cpp:35");
                return false;
            }

            ta::Console::success("FREETYPE: Successfully loaded font \"" + filename + "\"", "Font.cpp:35");

            return true;
        }

        bool Font::loadFromMemory(const unsigned char* location, signed long size, signed long index) {
            if (m_face) {
                FT_Done_Face(m_face);
            }

            if (!FT_New_Memory_Face(m_freetype, location, size, index, &m_face)) {
                ta::Console::error("FREETYPE: Failed to load font from memory", "Font.cpp:42");
                return false;
            }

            ta::Console::success("FREETYPE: Successfully loaded from memory", "Font.cpp:42");

            return true;
        }

        FT_Face& Font::getFontFace() {
            return m_face;
        }
    } /* graphics */
} /* ta */
