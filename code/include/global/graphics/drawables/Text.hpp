#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H
#include <string>

#include "global/graphics/Color.hpp"
#include "global/graphics/Drawable.hpp"
#include "global/graphics/ShaderProgram.hpp"
#include "global/graphics/Vertex.hpp"

namespace ta {
    namespace graphics {
        class Font;
        class Renderer;

        class Text: public Drawable {
        public:
            Text(ta::graphics::Font& font, const std::wstring& text = L"", int height = 42, float posX = 0.0f, float posY = 0.0f, ta::graphics::Color textColor = ta::graphics::Color(1.0f, 1.0f, 1.0f, 1.0f));
            virtual ~Text();

            void setFont(ta::graphics::Font& font);
            ta::graphics::Font& getFont() const;

            void setText(const std::wstring& text);
            void appendText(const std::wstring& text);
            void appendText(const wchar_t character);
            std::wstring getText() const;
            /// @brief Prepares the characters for the given string. If it's empty, the current text will be used.
            void prepare(const std::wstring& text = L"");

            void setHeight(int height);
            int getHeight();
            void setLineSpacing(int lineSpacing);
            int getLineSpacing();
            void setLetterSpacing(int letterSpacing);
            int getLetterSpacing();

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
            /* data */
            int m_height, m_lineSpacing, m_letterSpacing;
            float m_posX, m_posY;
            unsigned int m_vao, m_vbo;
            ta::graphics::Color m_textColor;
            std::wstring m_text;

            ta::graphics::Font& m_font;
            ta::graphics::ShaderProgram m_shader;
        };
    } /* graphics */
} /* ta */
