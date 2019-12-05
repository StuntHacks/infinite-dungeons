#include "global/graphics/Font.hpp"
#include "global/graphics/Renderer.hpp"
#include "global/graphics/Shader.hpp"
#include "global/graphics/drawables/Text.hpp"
#include "global/Console.hpp"
#include "switch/lock.hpp"

ta::graphics::ShaderProgram ta::graphics::Text::m_shader;

namespace ta {
    namespace graphics {
        Text::Text(ta::graphics::Font& font, const std::wstring& text, int height, int width, float posX, float posY, ta::graphics::Color textColor) :
        m_height(height),
        m_width(width),
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

                ta::graphics::Shader vsh, fsh;
                vsh.compile(vshSource, ta::graphics::Shader::Type::Vertex);
                fsh.compile(fshSource, ta::graphics::Shader::Type::Fragment);
                m_shader.attach(vsh).attach(fsh).link();

                glGenVertexArrays(1, &m_vao);
                glGenBuffers(1, &m_vbo);
                glBindVertexArray(m_vao);
                glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
                ta::graphics::Vertex vertices[6] = {
                    { { 0.0f, 1.0f, 0.5f }, { 0.0f, 1.0f, 0.0f, 0.5f }, { 0.0f, 1.0f } },
                    { { 0.0f, 0.0f, 0.5f }, { 0.0f, 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f } },
                    { { 1.0f, 0.0f, 0.5f }, { 0.0f, 1.0f, 0.0f, 0.5f }, { 1.0f, 0.0f } },

                    { { 1.0f, 0.0f, 0.5f }, { 0.0f, 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } },
                    { { 1.0f, 1.0f, 0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } },
                    { { 0.0f, 1.0f, 0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f } },
                };
                glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
                ta::graphics::Renderer::prepare();
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                glBindVertexArray(0);
            }
        }

        Text::~Text() {
            glDeleteBuffers(1, &m_vbo);
            glDeleteVertexArrays(1, &m_vao);
        }

        void Text::setFont(ta::graphics::Font& font) {
            m_font = font;
            _reloadFont();
        }

        ta::graphics::Font& Text::getFont() const {
            return m_font;
        }

        void Text::setText(const std::wstring& text) {
            m_text = text;
        }

        void Text::appendText(const std::wstring& text) {
            m_text += text;
        }

        std::wstring Text::getText() const {
            return m_text;
        }

        void Text::setHeight(int height) {
            m_height = height;
            _reloadFont();
        }

        int Text::getHeight() {
            return m_height;
        }

        void Text::setWidth(int width) {
            m_width = width;
            _reloadFont();
        }

        int Text::getWidth() {
            return m_width;
        }

        void Text::setDimensions(int height, int width) {
            m_height = height;
            m_width = width;
            _reloadFont();
        }

        void Text::setDimensions(ta::graphics::Vector2f dimensions) {
            m_height = dimensions.u;
            m_width = dimensions.v;
            _reloadFont();
        }

        ta::graphics::Vector2f Text::getDimensions() {
            return { static_cast<float>(m_height), static_cast<float>(m_width) };
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

        void Text::setPosition(ta::graphics::Vector2f dimensions) {
            m_posX = dimensions.u;
            m_posY = dimensions.v;
        }

        ta::graphics::Vector2f Text::getPosition() {
            return { static_cast<float>(m_posX), static_cast<float>(m_posY) };
        }

        void Text::setTextColor(ta::graphics::Color color) {
            m_textColor = color;
        }

        ta::graphics::Color Text::getTextColor() {
            return m_textColor;
        }

        void Text::draw(ta::graphics::Renderer& renderer, bool) {
            // ta::Lock lock(m_mutex);
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
                    y += m_height;
                    x = m_posX;
                    continue;
                }

                if (*c == '\r') {
                    continue;
                }

                Character ch = m_characters[*c];

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
                x += (ch.advance >> 6); // bitshift by 6 to get value in pixels (2^6 = 64)
            }

            glBindVertexArray(0);
            glBindTexture(GL_TEXTURE_2D, 0);

            renderer.getCurrentShader().use();
        }

        // private methods
        void Text::_reloadFont() {
            ta::Lock lock(m_mutex);
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

            FT_Set_Pixel_Sizes(m_font.getFontFace(), m_width, m_height);
            ta::Console::log("Height: " + std::to_string(m_height), "Text.cpp:239");

            FT_UInt index;
            FT_ULong character = FT_Get_First_Char(m_font.getFontFace(), &index);

            while (index) {
                if (FT_Load_Char(m_font.getFontFace(), character, FT_LOAD_RENDER)) {
                    ta::Console::error("FREETYPE: Failed to load Glyph", "Text.cpp:70");
                    character = FT_Get_Next_Char(m_font.getFontFace(), character, &index);
                    continue;
                }

                // generate texture
                GLuint texture;
                glGenTextures(1, &texture);
                glBindTexture(GL_TEXTURE_2D, texture);
                glTexImage2D(
                    GL_TEXTURE_2D,
                    0,
                    GL_RED,
                    m_font.getFontFace()->glyph->bitmap.width,
                    m_font.getFontFace()->glyph->bitmap.rows,
                    0,
                    GL_RED,
                    GL_UNSIGNED_BYTE,
                    m_font.getFontFace()->glyph->bitmap.buffer
                );

                // set texture options
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                // store character for later use
                Character charObject = {
                    texture,
                    glm::ivec2(m_font.getFontFace()->glyph->bitmap.width, m_font.getFontFace()->glyph->bitmap.rows),
                    glm::ivec2(m_font.getFontFace()->glyph->bitmap_left, m_font.getFontFace()->glyph->bitmap_top),
                    static_cast<GLuint>(m_font.getFontFace()->glyph->advance.x)
                };

                m_characters.insert(std::pair<FT_ULong, Character>(character, charObject));
                character = FT_Get_Next_Char(m_font.getFontFace(), character, &index);
            }
        }
    } /* graphics */
} /* ta */
