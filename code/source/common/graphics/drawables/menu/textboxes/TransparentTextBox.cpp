#include "pc/pc.hpp"
#include "switch/switch.hpp"
#include "common/graphics/Renderer.hpp"
#include "common/graphics/drawables/menu/textboxes/TransparentTextBox.hpp"
#include "opengl.hpp"

namespace id {
    namespace menu {
        TransparentTextBox::~TransparentTextBox() {
            glDeleteBuffers(1, &m_vbo);
            glDeleteVertexArrays(1, &m_vao);
        }

        void TransparentTextBox::draw(id::graphics::Renderer& renderer, bool) {
            if (m_state != id::menu::TextBox::State::PauseBefore && m_state != id::menu::TextBox::State::PauseAfter && m_state != id::menu::TextBox::State::Finished) {
                glBindVertexArray(m_vao);
                glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
                glBindVertexArray(0);

                m_textObject.draw(renderer, true);
            }
        }

        // protected methods
        TransparentTextBox::TransparentTextBox() :
        TextBox() {
            float height = 220.0f, shadowHeight = 40.0f, opacity = 0.55f;

            m_textObject.setTextColor(id::graphics::Color(1.0f, 1.0f, 1.0f, 1.0f));
            m_textObject.setPosition(50.0f, id::Display::getScreenHeight() - 160.0f);
            m_textObject.setHeight(50);
            m_textObject.setLineSpacing(10);

            m_vertices.push_back({
                { 0.0f, id::Display::getScreenHeight() - height, 0.0f },
                { 0.0f, 0.0f, 0.0f, opacity }
            });
            m_vertices.push_back({
                { id::Display::getScreenWidth(), id::Display::getScreenHeight() - height, 0.0f},
                { 0.0f, 0.0f, 0.0f, opacity }
            });
            m_vertices.push_back({
                { id::Display::getScreenWidth(), id::Display::getScreenHeight(), 0.0f },
                { 0.0f, 0.0f, 0.0f, opacity }
            });

            m_vertices.push_back({
                { 0.0f, id::Display::getScreenHeight() - height, 0.0f },
                { 0.0f, 0.0f, 0.0f, opacity }
            });
            m_vertices.push_back({
                { id::Display::getScreenWidth(), id::Display::getScreenHeight(), 0.0f},
                { 0.0f, 0.0f, 0.0f, opacity }
            });
            m_vertices.push_back({
                { 0.0f, id::Display::getScreenHeight(), 0.0f },
                { 0.0f, 0.0f, 0.0f, opacity }
            });

            m_vertices.push_back({
                { 0.0f, id::Display::getScreenHeight() - height, 0.0f },
                { 0.0f, 0.0f, 0.0f, opacity }
            });
            m_vertices.push_back({
                { id::Display::getScreenWidth(), id::Display::getScreenHeight() - height, 0.0f},
                { 0.0f, 0.0f, 0.0f, opacity }
            });
            m_vertices.push_back({
                { 0.0f, id::Display::getScreenHeight() - height - shadowHeight, 0.0f },
                { 0.0f, 0.0f, 0.0f, 0.0f }
            });

            m_vertices.push_back({
                { 0.0f, id::Display::getScreenHeight() - height - shadowHeight, 0.0f },
                { 0.0f, 0.0f, 0.0f, 0.0f }
            });
            m_vertices.push_back({
                { id::Display::getScreenWidth(), id::Display::getScreenHeight() - height - shadowHeight, 0.0f},
                { 0.0f, 0.0f, 0.0f, 0.0f }
            });
            m_vertices.push_back({
                { id::Display::getScreenWidth(), id::Display::getScreenHeight() - height, 0.0f },
                { 0.0f, 0.0f, 0.0f, opacity }
            });

            glGenVertexArrays(1, &m_vao);
            glGenBuffers(1, &m_vbo);
            // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
            glBindVertexArray(m_vao);

            glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
            id::graphics::Renderer::prepare();
            glBufferData(GL_ARRAY_BUFFER, sizeof(id::graphics::Vertex) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW);

            // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
            // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
            glBindVertexArray(0);
        }
    } /* menu */
} /* id */
