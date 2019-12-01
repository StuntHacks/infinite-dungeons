#include "global/graphics/Shader.hpp"
#include "global/Console.hpp"

#include <fstream>

namespace ta {
    namespace graphics {
        Shader::~Shader() {
            glDeleteShader(m_shader);
        }

        bool Shader::compile(const std::string& source, ta::graphics::Shader::Type type) {
            m_type = type;

            GLint success;
            GLchar msg[512];

            glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);

            if (success) {
                glDeleteShader(m_shader);
            }

            m_shader = glCreateShader(static_cast<GLenum>(type));

            if (!m_shader) {
                ta::Console::error("OpenGL: " + std::to_string(static_cast<GLenum>(type)) + ": cannot create shader", "Shader.cpp:24");
                return false;
            }

            const char* src = source.c_str();

            glShaderSource(m_shader, 1, &src, nullptr);
            glCompileShader(m_shader);
            glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);

            if (!success) {
                glGetShaderInfoLog(m_shader, sizeof(msg), nullptr, msg);
                ta::Console::error("OpenGL: " + std::to_string(static_cast<GLenum>(type)) + msg, "Shader.cpp:35");
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
    } /* graphics */
} /* ta */
