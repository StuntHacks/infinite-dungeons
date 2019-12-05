#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H
#include <map>
#include <string>

#include "opengl.hpp"
#include "global/graphics/Color.hpp"
#include "global/graphics/Drawable.hpp"
#include "global/graphics/ShaderProgram.hpp"
#include "global/graphics/Vertex.hpp"
#include "switch/mutex.hpp"

namespace ta {
    namespace graphics {
        class Font;
        class Renderer;

        class Text: public Drawable {
        public:
            Text(ta::graphics::Font& font, const std::wstring& text = L"", int height = 42, int width = 0, float posX = 0.0f, float posY = 0.0f, ta::graphics::Color textColor = ta::graphics::Color(1.0f, 1.0f, 1.0f, 1.0f));
            virtual ~Text();

            void setFont(ta::graphics::Font& font);
            ta::graphics::Font& getFont() const;

            void setText(const std::wstring& text);
            void appendText(const std::wstring& text);
            std::wstring getText() const;

            void setHeight(int height);
            int getHeight();
            void setWidth(int width);
            int getWidth();
            void setDimensions(int height, int width);
            void setDimensions(ta::graphics::Vector2f dimensions);
            ta::graphics::Vector2f getDimensions();

            void setPosX(float posX);
            float getPosX();
            void setPosY(float posY);
            float getPosY();
            void setPosition(float posX, float posY);
            void setPosition(ta::graphics::Vector2f dimensions);
            ta::graphics::Vector2f getPosition();

            void setTextColor(ta::graphics::Color color);
            ta::graphics::Color getTextColor();

            virtual void draw(ta::graphics::Renderer& renderer, bool);

        private:
            void _reloadFont();

            struct Character {
                GLuint     texture; // ID handle of the glyph texture
                glm::ivec2 size;    // Size of glyph
                glm::ivec2 bearing; // Offset from baseline to left/top of glyph
                GLuint     advance; // Offset to advance to next glyph
            };

            /* data */
            int m_height, m_width;
            float m_posX, m_posY;
            unsigned int m_vao, m_vbo;
            ta::graphics::Color m_textColor;
            std::wstring m_text;
            std::map<FT_ULong, ta::graphics::Text::Character> m_characters;

            ta::Mutex m_mutex;
            ta::graphics::Font& m_font;
            static ta::graphics::ShaderProgram m_shader;
        };
    } /* graphics */
} /* ta */
