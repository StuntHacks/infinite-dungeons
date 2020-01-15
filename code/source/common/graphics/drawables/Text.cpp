#include "common/graphics/Font.hpp"
#include "common/graphics/Renderer.hpp"
#include "common/graphics/Shader.hpp"
#include "common/graphics/drawables/Text.hpp"
#include "switch/lock.hpp"

namespace id {
    namespace graphics {
        Text::Text(id::graphics::Font& font, const std::wstring& text, int height, float posX, float posY, id::graphics::Color textColor) :
        m_height(height),
        m_lineSpacing(0),
        m_letterSpacing(0),
        m_posX(posX),
        m_posY(posY),
        m_textColor(textColor),
        m_text(text),
        m_font(font) {
            setFont(font);

            if (m_shader.getID() == 0) {
                const std::string vshSource = R"text(
                #version 330 core
                layout (location = 0) in vec3 iPos;
                layout (location = 1) in vec4 iColor;
                layout (location = 2) in vec2 iTexCoords;
                layout (location = 3) in vec3 iNormals;
                out vec4 color;
                out vec2 texCoords;

                uniform mat4 projection;
                uniform mat4 transform;
                uniform vec4 textColor;

                void main()
                {
                    gl_Position = projection * transform * vec4(iPos.xy, 0.0, 1.0);
                    color = textColor;
                    texCoords = iTexCoords;
                }
                )text";

                const std::string fshSource = R"text(
                #version 330 core
                in vec4 color;
                in vec2 texCoords;
                out vec4 oColor;

                uniform sampler2D text;

                void main()
                {
                    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, texCoords).r);
                    oColor = color * sampled;
                }
                )text";

                id::graphics::Shader vsh, fsh;
                vsh.compile(vshSource, id::graphics::Shader::Type::Vertex);
                fsh.compile(fshSource, id::graphics::Shader::Type::Fragment);
                m_shader.attach(vsh).attach(fsh).link();

                glGenVertexArrays(1, &m_vao);
                glGenBuffers(1, &m_vbo);
                glBindVertexArray(m_vao);
                glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
                id::graphics::Vertex vertices[6] = {
                    { { 0.0f, 1.0f, 0.5f }, { 0.0f, 1.0f, 0.0f, 0.5f }, { 0.0f, 1.0f } },
                    { { 0.0f, 0.0f, 0.5f }, { 0.0f, 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f } },
                    { { 1.0f, 0.0f, 0.5f }, { 0.0f, 1.0f, 0.0f, 0.5f }, { 1.0f, 0.0f } },

                    { { 1.0f, 0.0f, 0.5f }, { 0.0f, 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } },
                    { { 1.0f, 1.0f, 0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } },
                    { { 0.0f, 1.0f, 0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f } },
                };
                glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
                id::graphics::Renderer::prepare();
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                glBindVertexArray(0);
            }
        }

        Text::~Text() {
            glDeleteBuffers(1, &m_vbo);
            glDeleteVertexArrays(1, &m_vao);
        }

        void Text::setFont(id::graphics::Font& font) {
            m_font = font;
        }

        id::graphics::Font& Text::getFont() const {
            return m_font;
        }

        void Text::setText(const std::wstring& text) {
            m_text = text;
        }

        void Text::appendText(const std::wstring& text) {
            m_text += text;
        }

        void Text::appendText(const wchar_t character) {
            m_text += character;
        }

        std::wstring Text::getText() const {
            return m_text;
        }

        void Text::prepare(const std::wstring& text) {
            std::wstring::const_iterator c;

            if (text == L"") {
                for (c = m_text.begin(); c != m_text.end(); c++) {
                    m_font.getCharacter(*c, m_height);
                }
            } else {
                for (c = text.begin(); c != text.end(); c++) {
                    m_font.getCharacter(*c, m_height);
                }
            }
        }

        void Text::setHeight(int height) {
            m_height = height;
        }

        int Text::getHeight() {
            return m_height;
        }

        void Text::setLineSpacing(int lineSpacing) {
            m_lineSpacing = lineSpacing;
        }

        int Text::getLineSpacing() {
            return m_lineSpacing;
        }

        void Text::setLetterSpacing(int letterSpacing) {
            m_letterSpacing = letterSpacing;
        }

        int Text::getLetterSpacing() {
            return m_letterSpacing;
        }

        void Text::setPosX(float posX) {
            m_posX = posX;
        }

        float Text::getPosX() {
            return m_posX;
        }

        void Text::setPosY(float posY) {
            m_posY = posY;
        }

        float Text::getPosY() {
            return m_posY;
        }

        void Text::setPosition(float posX, float posY) {
            m_posX = posX;
            m_posY = posY;
        }

        void Text::setPosition(id::graphics::Vector2f dimensions) {
            m_posX = dimensions.u;
            m_posY = dimensions.v;
        }

        id::graphics::Vector2f Text::getPosition() {
            return { static_cast<float>(m_posX), static_cast<float>(m_posY) };
        }

        void Text::setTextColor(id::graphics::Color color) {
            m_textColor = color;
        }

        id::graphics::Color Text::getTextColor() {
            return m_textColor;
        }

        void Text::draw(id::graphics::Renderer& renderer, bool) {
            m_shader.use();
            m_shader.setMatrix4("projection", renderer.getOrthoProjection());
            m_shader.setVector4f("textColor", { m_textColor.getRed(), m_textColor.getGreen(), m_textColor.getBlue(), m_textColor.getAlpha() });

            GLfloat x = m_posX;
            GLfloat y = m_posY;

            glActiveTexture(GL_TEXTURE0);
            glBindVertexArray(m_vao);

            // iterate through all characters
            std::wstring::const_iterator c;
            for (c = m_text.begin(); c != m_text.end(); c++) {
                if (*c == '\n') {
                    y += m_height + m_lineSpacing;
                    x = m_posX;
                    continue;
                }

                if (*c == '\\') {
                    if (std::next(c) == m_text.end()) {
                        continue;
                    }

                    c++;

                    switch (*c) {
                    case 'r':
                        m_shader.setVector4f("textColor", { 1.0f, 0.2f, 0.25f, m_textColor.getAlpha() });
                        continue;
                    case 'g':
                        m_shader.setVector4f("textColor", { 0.0f, 1.0f, 0.4f, m_textColor.getAlpha() });
                        continue;
                    case 'b':
                        m_shader.setVector4f("textColor", { 0.4f, 0.6f, 1.0f, m_textColor.getAlpha() });
                        continue;
                    case 'c':
                        m_shader.setVector4f("textColor", { 0.2f, 1.0f, 1.0f, m_textColor.getAlpha() });
                        continue;
                    case 'm':
                        m_shader.setVector4f("textColor", { 1.0f, 0.4f, 0.9f, m_textColor.getAlpha() });
                        continue;
                    case 'y':
                        m_shader.setVector4f("textColor", { 1.0f, 1.0f, 0.3f, m_textColor.getAlpha() });
                        continue;
                    case 'd':
                        m_shader.setVector4f("textColor", { m_textColor.getRed(), m_textColor.getGreen(), m_textColor.getBlue(), m_textColor.getAlpha() });
                        continue;
                    default:
                        /* code */
                        break;
                    }
                }

                if (*c == '\r') {
                    continue;
                }

                id::graphics::Font::Character ch = m_font.getCharacter(*c, m_height);

                GLfloat xpos = x + ch.bearing.x;
                GLfloat ypos = y - ch.bearing.y;

                GLfloat w = ch.size.x;
                GLfloat h = ch.size.y;

                glBindTexture(GL_TEXTURE_2D, ch.texture);

                glm::mat4 transform(1.0f);
                transform = glm::translate(transform, glm::vec3(xpos, ypos, 0.0f));
                transform = glm::scale(transform, glm::vec3(w, h, 1.0f));
                m_shader.setMatrix4("transform", transform);

                glDrawArrays(GL_TRIANGLES, 0, 6);

                // advance is in 1/64 pixels
                x += (ch.advance >> 6) + m_letterSpacing; // bitshift by 6 to get value in pixels (2^6 = 64)
            }

            glBindVertexArray(0);
            glBindTexture(GL_TEXTURE_2D, 0);

            renderer.getCurrentShader().use();
        }
    } /* graphics */
} /* id */
