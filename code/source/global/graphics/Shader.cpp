#include "global/graphics/Shader.hpp"

#include <fstream>
#include <stdio.h>

namespace ta {
    namespace graphics {
        Shader::~Shader() {
            glDeleteShader(m_shader);
        }

        bool Shader::compile(const std::string& source, ta::graphics::Shader::Type type) {
            m_type = type;
            GLenum glType = typeToGL(type);

            GLint success;
            GLchar msg[512];

            glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);

            if (success) {
                glDeleteShader(m_shader);
            }

            m_shader = glCreateShader(glType);

            if (!m_shader) {
                printf("OpenGL: %u: cannot create shader\n", glType);
                return false;
            }

            const char* src = source.c_str();

            glShaderSource(m_shader, 1, &src, nullptr);
            glCompileShader(m_shader);
            glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);

            if (!success) {
                glGetShaderInfoLog(m_shader, sizeof(msg), nullptr, msg);
                printf("OpenGL: %u: %s\n", glType, msg);
                glDeleteShader(m_shader);
                return false;
            }

            return true;
        }

        bool Shader::load(const std::string& filepath, ta::graphics::Shader::Type type) {
            std::ifstream filestream(filepath);
            std::string source((std::istreambuf_iterator<char>(filestream)),
                                std::istreambuf_iterator<char>());

            return compile(source, type);
        }

        ta::graphics::Shader::Type Shader::getType() const {
            return m_type;
        }

        unsigned int Shader::getID() const {
            return m_shader;
        }

        GLenum Shader::typeToGL(ta::graphics::Shader::Type type) {
            switch (type) {
            case ta::graphics::Shader::Type::Vertex:
                return GL_VERTEX_SHADER;
                break;
            case ta::graphics::Shader::Type::TesselationControl:
                return GL_TESS_CONTROL_SHADER;
                break;
            case ta::graphics::Shader::Type::TesselationEvaluation:
                return GL_TESS_EVALUATION_SHADER;
                break;
            case ta::graphics::Shader::Type::Geometry:
                return GL_GEOMETRY_SHADER;
                break;
            case ta::graphics::Shader::Type::Fragment:
                return GL_FRAGMENT_SHADER;
                break;
            case ta::graphics::Shader::Type::Compute:
                return GL_COMPUTE_SHADER;
                break;
            default:
                return GL_NONE;
            }
        }
    } /* graphics */
} /* ta */
