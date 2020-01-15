#include "global/graphics/RenderTarget.hpp"
#include "global/graphics/Renderer.hpp"

#include <glad/glad.h>

namespace id {
    namespace graphics {
        RenderTarget::RenderTarget(float width, float height) :
        m_width(width),
        m_height(height),
        m_framebuffer(0),
        m_texture(0) {
            glGenFramebuffers(1, &m_framebuffer);

            bind();
            glGenTextures(1, &m_texture);
            glBindTexture(GL_TEXTURE_2D, m_texture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);
            unbind();

            m_vertices.push_back({
                { 0.0f, height, 0.0f },
                { 0.0f, 1.0f, 1.0f, 1.0f },
                { 0.0f, 1.0f }
            });
            m_vertices.push_back({
                { width, height, 0.0f},
                { 1.0f, 1.0f, 1.0f, 1.0f },
                { 1.0f, 1.0f }
            });
            m_vertices.push_back({
                { width, 0.0f, 0.0f },
                { 1.0f, 0.0f, 1.0f, 1.0f },
                { 0.0f, 0.0f }
            });

            m_vertices.push_back({
                { 0.0f, height, 0.0f },
                { 0.0f, 0.0f, 0.0f, 1.0f },
                { 0.0f, 0.0f }
            });
            m_vertices.push_back({
                { width, 0.0f, 0.0f},
                { 0.0f, 0.0f, 0.0f, 1.0f },
                { 0.0f, 0.0f }
            });
            m_vertices.push_back({
                { 0.0f, 0.0f, 0.0f },
                { 0.0f, 0.0f, 0.0f, 1.0f },
                { 0.0f, 0.0f }
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

        RenderTarget::~RenderTarget() {
            glDeleteFramebuffers(1, &m_framebuffer);
        }

        void RenderTarget::bind() {
            glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
        }

        void RenderTarget::unbind() {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        void RenderTarget::setPosX(float posX) {
            m_posX = posX;
        }

        float RenderTarget::getPosX() {
            return m_posX;
        }

        void RenderTarget::setPosY(float posY) {
            m_posY = posY;
        }

        float RenderTarget::getPosY() {
            return m_posY;
        }

        void RenderTarget::setPosition(float posX, float posY) {
            m_posX = posX;
            m_posY = posY;
        }

        void RenderTarget::setPosition(id::graphics::Vector2f dimensions) {
            m_posX = dimensions.u;
            m_posY = dimensions.v;
        }

        id::graphics::Vector2f RenderTarget::getPosition() {
            return { static_cast<float>(m_posX), static_cast<float>(m_posY) };
        }

        void RenderTarget::draw(id::graphics::Renderer& renderer, bool) {
            glActiveTexture(GL_TEXTURE0);
            glBindVertexArray(m_vao);
            glBindTexture(GL_TEXTURE_2D, m_texture);

            glm::mat4 transform;
            // transform = glm::translate(transform, glm::vec3(m_posX, m_posY, 0.0f));
            // renderer.getCurrentShader().setMatrix4("transform", transform);

            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        unsigned int RenderTarget::getTexture() const {
            return m_texture;
        }
    } /* graphics */
} /* id */
