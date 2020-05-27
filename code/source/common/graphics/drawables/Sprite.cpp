#include "common/graphics/drawables/Sprite.hpp"
#include "common/graphics/Renderer.hpp"
#include "common/graphics/Shader.hpp"
#include "common/Console.hpp"
#include "opengl.hpp"

namespace id {
    namespace graphics {
        Sprite::Sprite() :
        m_posX(0.0f),
        m_posY(0.0f),
        m_width(0.0f),
        m_height(0.0f),
        m_rotation(0.0f),
        m_opacity(1.0f),
        m_color(1.0f, 1.0f, 1.0f, 1.0f) {
            id::graphics::Shader vsh, fsh;
            vsh.load("romfs:/shaders/generic/texturedPolygon.vert", id::graphics::Shader::Type::Vertex);
            fsh.load("romfs:/shaders/generic/texturedPolygon.frag", id::graphics::Shader::Type::Fragment);

            m_shader.attach(vsh).attach(fsh).link();

            glGenVertexArrays(1, &m_vao);
            glGenBuffers(1, &m_vbo);

            m_vertices.push_back({
                { 0.0f, 0.0f, 0.5f },
                { 0.0f, 0.0f, 0.0f, 0.0f },
                { 0.0f, 0.0f }
            });
            m_vertices.push_back({
                { 0.0f, 1.0f, 0.5f },
                { 0.0f, 0.0f, 0.0f, 0.0f },
                { 0.0f, 1.0f }
            });
            m_vertices.push_back({
                { 1.0f, 1.0f, 0.5f },
                { 0.0f, 0.0f, 0.0f, 0.0f },
                { 1.0f, 1.0f }
            });

            m_vertices.push_back({
                { 1.0f, 1.0f, 0.5f },
                { 0.0f, 0.0f, 0.0f, 0.0f },
                { 1.0f, 1.0f }
            });
            m_vertices.push_back({
                { 1.0f, 0.0f, 0.5f },
                { 0.0f, 0.0f, 0.0f, 0.0f },
                { 1.0f, 0.0f }
            });
            m_vertices.push_back({
                { 0.0f, 0.0f, 0.5f },
                { 0.0f, 0.0f, 0.0f, 0.0f },
                { 0.0f, 0.0f }
            });

            glBindVertexArray(m_vao);
            glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
            id::graphics::Renderer::prepare();
            glBufferData(GL_ARRAY_BUFFER, sizeof(id::graphics::Vertex) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        Sprite::~Sprite() {
            glDeleteBuffers(1, &m_vbo);
            glDeleteVertexArrays(1, &m_vao);
        }

        // texture
        void Sprite::setTexture(id::graphics::Texture& texture) {
            m_texture = texture;
            m_texture.setAutoDelete(false);
        }

        id::graphics::Texture& Sprite::getTexture() {
            return m_texture;
        }

        // dimensions
        void Sprite::setWidth(float width) {
            m_width = width;
        }

        float Sprite::getWidth() {
            return m_width;
        }

        void Sprite::setHeight(float height) {
            m_height = height;
        }

        float Sprite::getHeight() {
            return m_height;
        }

        void Sprite::setDimensions(float width, float height) {
            m_width = width;
            m_height = height;
        }

        void Sprite::setDimensions(id::graphics::Vector2f dimensions) {
            m_width = dimensions.u;
            m_height = dimensions.v;
        }

        id::graphics::Vector2f Sprite::getDimensions() {
            return { m_width, m_height };
        }

        // position
        void Sprite::setPositionX(float posX) {
            m_posX = posX;
        }

        void Sprite::moveX(float delta) {
            m_posX += delta;
        }

        float Sprite::getPositionX() {
            return m_posX;
        }

        void Sprite::setPositionY(float posY) {
            m_posY = posY;
        }

        void Sprite::moveY(float delta) {
            m_posY += delta;
        }

        float Sprite::getPositionY() {
            return m_posY;
        }

        void Sprite::setPosition(float posX, float posY) {
            m_posX = posX;
            m_posY = posY;
        }

        void Sprite::setPosition(id::graphics::Vector2f position) {
            m_posX = position.u;
            m_posY = position.v;
        }

        void Sprite::move(float deltaX, float deltaY) {
            m_posX += deltaX;
            m_posY += deltaY;
        }

        id::graphics::Vector2f Sprite::getPosition() {
            return { m_posX, m_posY };
        }

        // rotation
        void Sprite::setRotation(float rotation) {
            m_rotation = glm::radians(rotation);
        }

        void Sprite::rotate(float delta) {
            m_rotation += glm::radians(delta);
        }

        float Sprite::getRotation() {
            return glm::degrees(m_rotation);
        }

        // opacity
        void Sprite::setOpacity(float opacity) {
            m_opacity = opacity;
        }

        float Sprite::getOpacity() {
            return m_opacity;
        }

        // color
        void Sprite::setColor(id::graphics::Color color) {
            m_color = color;
        }

        id::graphics::Color Sprite::getColor() {
            return m_color;
        }

        // shader
        void Sprite::setShader(id::graphics::ShaderProgram& shader) {
            m_shader = shader;
        }

        id::graphics::ShaderProgram& Sprite::getShader() {
            return m_shader;
        }

        // drawing
        void Sprite::draw(id::graphics::Renderer& renderer, bool) {
            m_shader.use();

            m_shader.setFloat("opacity", m_opacity);
            m_shader.setVector3f("color", { m_color.getRed(), m_color.getGreen(), m_color.getBlue() });
            m_shader.setMatrix4("projection", renderer.getOrthoProjection());

            glm::mat4 transform(1.0f);
            transform = glm::translate(transform, glm::vec3(m_posX, m_posY, 0.0f));
            transform = glm::scale(transform, glm::vec3(m_width, m_height, 1.0f));
            transform = glm::rotate(transform, glm::radians(m_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
            m_shader.setMatrix4("transform", transform);

            glBindVertexArray(m_vao);
            m_texture.bind();
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
            glBindVertexArray(0);
            glBindTexture(GL_TEXTURE_2D, 0);

            renderer.getCurrentShader().use();
        }
    } /* graphics */
} /* id */
