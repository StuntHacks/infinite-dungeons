#pragma once

#include <glad/glad.h>
#include <string>

namespace id {
    namespace graphics {
        /**
         * @brief A single OpenGL shader
         */
        class Shader {
        public:
            enum class Type {
                Vertex = GL_VERTEX_SHADER,
                TesselationControl = GL_TESS_CONTROL_SHADER,
                TesselationEvaluation = GL_TESS_EVALUATION_SHADER,
                Geometry = GL_GEOMETRY_SHADER,
                Fragment = GL_FRAGMENT_SHADER,
                Compute = GL_COMPUTE_SHADER
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
            bool compile(const std::string& source, id::graphics::Shader::Type type);

            /**
             * @brief Loads a shader from a given file path
             * @param filepath The path of the shader source code
             * @param type     The shader type
             * @return         Whether the loading of the shader was successful
             * @retval true    The shader was successfully loaded and compiled
             * @retval false   The compilation of the shader resulted in an error
             */
            bool load(const std::string& filepath, id::graphics::Shader::Type type);

            /**
             * @brief Returns the type of the shader
             * @return The shader type
             */
            id::graphics::Shader::Type getType() const;

            /**
             * @brief Returns the ID of the shader ready to be used with OpenGL
             * @return The ID
             */
            unsigned int getID() const;

        private:
            /* data */
            id::graphics::Shader::Type m_type;
            unsigned int m_shader;
        };
    } /* graphics */
} /* id */
