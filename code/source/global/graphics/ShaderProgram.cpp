#include "global/graphics/ShaderProgram.hpp"
#include "global/graphics/Shader.hpp"

#include <glad/glad.h>
#include <stdio.h>

namespace ta {
    namespace graphics {
        ShaderProgram::ShaderProgram() :
            m_program(0) { /* do nothing */ }

        ShaderProgram::~ShaderProgram() {
            glDeleteProgram(m_program);
        }

        ShaderProgram& ShaderProgram::attach(const ta::graphics::Shader& shader) {
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
                    printf("ShaderProgram: Link error: %s\n", buf);
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
    } /* graphics */
} /* ta */
