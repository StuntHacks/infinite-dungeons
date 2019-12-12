#include "global/graphics/Font.hpp"
#include "global/Console.hpp"
#include "switch/lock.hpp"

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

        ta::graphics::Font::Character Font::getCharacter(wchar_t character, int height) {
            Character ch;
            ch.valid = false;
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

            if (m_characters.count(character) != 0) {
                if (m_characters[character].count(height) != 0) {
                    return m_characters[character][height];
                }
            }

            {
                ta::Lock lock(m_mutex);
                FT_Set_Pixel_Sizes(m_face, 0, height);

                if (FT_Load_Char(m_face, character, FT_LOAD_RENDER)) {
                    return ch;
                }

                // generate texture
                GLuint texture;
                glGenTextures(1, &texture);
                glBindTexture(GL_TEXTURE_2D, texture);
                glTexImage2D(
                    GL_TEXTURE_2D,
                    0,
                    GL_RED,
                    m_face->glyph->bitmap.width,
                    m_face->glyph->bitmap.rows,
                    0,
                    GL_RED,
                    GL_UNSIGNED_BYTE,
                    m_face->glyph->bitmap.buffer
                );

                // set texture options
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                // store character for later use
                ch.texture = texture;
                ch.size = glm::ivec2(m_face->glyph->bitmap.width, m_face->glyph->bitmap.rows);
                ch.bearing = glm::ivec2(m_face->glyph->bitmap_left, m_face->glyph->bitmap_top);
                ch.advance = static_cast<GLuint>(m_face->glyph->advance.x);
                ch.valid = true;

                m_characters[character][height] = ch;
            }

            return ch;
        }
    } /* graphics */
} /* ta */
