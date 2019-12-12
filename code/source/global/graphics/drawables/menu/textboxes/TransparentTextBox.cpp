#include "global/graphics/Renderer.hpp"
#include "global/graphics/drawables/menu/textboxes/TransparentTextBox.hpp"
#include "opengl.hpp"

namespace ta {
    namespace menu {
        ta::menu::TransparentTextBox& TransparentTextBox::getInstance() {
            static ta::menu::TransparentTextBox instance;
            return instance;
        }

        TransparentTextBox::~TransparentTextBox() {
            glDeleteBuffers(1, &m_vbo);
            glDeleteVertexArrays(1, &m_vao);
        }

        void TransparentTextBox::draw(ta::graphics::Renderer& renderer, bool) {
            if (m_state != ta::menu::TextBox::State::PauseBefore && m_state != ta::menu::TextBox::State::PauseAfter && m_state != ta::menu::TextBox::State::Finished) {
                glBindVertexArray(m_vao);
                glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
                glBindVertexArray(0);

                m_textObject.draw(renderer, true);
            }
        }

        // protected methods
        TransparentTextBox::TransparentTextBox() :
        TextBox() {
            float height = 220.0f, shadowHeight = 40.0f, opacity = 0.7f;

            m_textObject.setTextColor(ta::graphics::Color(1.0f, 1.0f, 1.0f, 1.0f));
            m_textObject.setPosition(50.0f, 920.0f);
            m_textObject.setHeight(50);
            m_textObject.setLineSpacing(10);

            m_vertices.push_back({
                { 0.0f, 1080.0f - height, 0.0f },
                { 0.0f, 0.0f, 0.0f, opacity }
            });
            m_vertices.push_back({
                { 1920.0f, 1080.0f - height, 0.0f},
                { 0.0f, 0.0f, 0.0f, opacity }
            });
            m_vertices.push_back({
                { 1920.0f, 1080.0f, 0.0f },
                { 0.0f, 0.0f, 0.0f, opacity }
            });

            m_vertices.push_back({
                { 0.0f, 1080.0f - height, 0.0f },
                { 0.0f, 0.0f, 0.0f, opacity }
            });
            m_vertices.push_back({
                { 1920.0f, 1080.0f, 0.0f},
                { 0.0f, 0.0f, 0.0f, opacity }
            });
            m_vertices.push_back({
                { 0.0f, 1080.0f, 0.0f },
                { 0.0f, 0.0f, 0.0f, opacity }
            });

            m_vertices.push_back({
                { 0.0f, 1080.0f - height, 0.0f },
                { 0.0f, 0.0f, 0.0f, opacity }
            });
            m_vertices.push_back({
                { 1920.0f, 1080.0f - height, 0.0f},
                { 0.0f, 0.0f, 0.0f, opacity }
            });
            m_vertices.push_back({
                { 0.0f, 1080.0f - height - shadowHeight, 0.0f },
                { 0.0f, 0.0f, 0.0f, 0.0f }
            });

            m_vertices.push_back({
                { 0.0f, 1080.0f - height - shadowHeight, 0.0f },
                { 0.0f, 0.0f, 0.0f, 0.0f }
            });
            m_vertices.push_back({
                { 1920.0f, 1080.0f - height - shadowHeight, 0.0f},
                { 0.0f, 0.0f, 0.0f, 0.0f }
            });
            m_vertices.push_back({
                { 1920.0f, 1080.0f - height, 0.0f },
                { 0.0f, 0.0f, 0.0f, opacity }
            });

            glGenVertexArrays(1, &m_vao);
            glGenBuffers(1, &m_vbo);
            // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
            glBindVertexArray(m_vao);

            glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
            ta::graphics::Renderer::prepare();
            glBufferData(GL_ARRAY_BUFFER, sizeof(ta::graphics::Vertex) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW);

            // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
            // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
            glBindVertexArray(0);
        }
    } /* menu */
} /* ta */
