#pragma once

#include <glad/glad.h>
#include <string>

namespace ta {
    namespace graphics {
        /**
         * @brief A single OpenGL shader
         */
        class Shader {
        public:
            enum class Type {
                Vertex,
                TesselationControl,
                TesselationEvaluation,
                Geometry,
                Fragment,
                Compute
            };

            /**
             * @brief Destructs the shader
             */
            ~Shader();

            /**
             * @brief Compiles a shader from the given source code
             * @param source The shader source code
             * @param type   The shader type.
             * @return       Whether the compilation of the shader was successful
             * @retval true  The shader was successfully compiled
             * @retval false The compilation of the shader resulted in an error
             */
            bool compile(const std::string& source, ta::graphics::Shader::Type type);

            /**
             * @brief Loads a shader from a given file path
             * @param filepath The path of the shader source code
             * @param type     The shader type
             * @return         Whether the loading of the shader was successful
             * @retval true    The shader was successfully loaded and compiled
             * @retval false   The compilation of the shader resulted in an error
             */
            bool load(const std::string& filepath, ta::graphics::Shader::Type type);

            /**
             * @brief Returns the type of the shader
             * @return The shader type
             */
            ta::graphics::Shader::Type getType() const;

            /**
             * @brief Returns the ID of the shader ready to be used with OpenGL
             * @return The ID
             */
            unsigned int getID() const;

            /**
             * @brief Converts a ta::graphics::Shader::Type to an OpenGL shader type
             * @param  type The type to convert
             * @return      The converted type
             */
            static GLenum typeToGL(ta::graphics::Shader::Type type);

        private:
            /* data */
            ta::graphics::Shader::Type m_type;
            unsigned int m_shader;
        };
    } /* graphics */
} /* ta */
