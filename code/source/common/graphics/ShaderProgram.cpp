#include "common/graphics/ShaderProgram.hpp"
#include "common/graphics/Shader.hpp"
#include "common/Console.hpp"
#include "opengl.hpp"

#include <stdio.h>

namespace id {
    namespace graphics {
        ShaderProgram::ShaderProgram() :
            m_program(0) { /* do nothing */ }

        ShaderProgram::~ShaderProgram() {
            glDeleteProgram(m_program);
        }

        ShaderProgram& ShaderProgram::attach(const id::graphics::Shader& shader) {
            if (m_program == 0) {
                m_program = glCreateProgram();
                m_created = true;
            }

            glAttachShader(m_program, shader.getID());
            return *this;
        }

        bool ShaderProgram::link() {
            GLint success;
            glGetProgramiv(m_program, GL_LINK_STATUS, &success);

            if (!success) {
                glLinkProgram(m_program);
                glGetProgramiv(m_program, GL_LINK_STATUS, &success);

                if (!success) {
                    char buf[512];
                    glGetProgramInfoLog(m_program, sizeof(buf), nullptr, buf);
                    id::Console::error("Link error " + std::string(buf), "ShaderProgram.cpp:" + std::to_string(__LINE__));
                    return false;
                }

                return true;
            }

            return false;
        }

        void ShaderProgram::reset() {
            if (m_program != 0) {
                glDeleteProgram(m_program);
                m_program = glCreateProgram();
                m_linked = false;
            }
        }

        bool ShaderProgram::use() const {
            GLint success;
            glGetProgramiv(m_program, GL_LINK_STATUS, &success);

            if (success) {
                glUseProgram(m_program);
                return true;
            }

            return false;
        }

        const unsigned int ShaderProgram::getID() const {
            return m_program;
        }

        void ShaderProgram::setFloat(const std::string& name, float value) {
            glUniform1f(glGetUniformLocation(m_program, name.c_str()), value);
        }

        void ShaderProgram::setInteger(const std::string& name, int value) {
            glUniform1i(glGetUniformLocation(m_program, name.c_str()), value);
        }

        void ShaderProgram::setVector2f(const std::string& name, float x, float y) {
            glUniform2f(glGetUniformLocation(m_program, name.c_str()), x, y);
        }

        void ShaderProgram::setVector2f(const std::string& name, const id::graphics::Vector2f& value) {
            glUniform2f(glGetUniformLocation(m_program, name.c_str()), value.u, value.v);
        }

        void ShaderProgram::setVector3f(const std::string& name, float x, float y, float z) {
            glUniform3f(glGetUniformLocation(m_program, name.c_str()), x, y, z);
        }

        void ShaderProgram::setVector3f(const std::string& name, const id::graphics::Vector3f& value) {
            glUniform3f(glGetUniformLocation(m_program, name.c_str()), value.x, value.y, value.z);
        }

        void ShaderProgram::setVector4f(const std::string& name, float x, float y, float z, float w) {
            glUniform4f(glGetUniformLocation(m_program, name.c_str()), x, y, z, w);
        }

        void ShaderProgram::setVector4f(const std::string& name, const id::graphics::Vector4f& value) {
            glUniform4f(glGetUniformLocation(m_program, name.c_str()), value.x, value.y, value.z, value.w);
        }

        void ShaderProgram::setMatrix4(const std::string& name, const glm::mat4& matrix) {
            glUniformMatrix4fv(glGetUniformLocation(m_program, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
        }
    } /* graphics */
} /* id */
