#pragma once

#include <string>

#include "opengl.hpp"

#include "Vertex.hpp"

namespace id {
    namespace graphics {
        class Shader;

        /**
         * @brief Combines multiple different shaders in order to use them in union
         */
        class ShaderProgram {
        public:
            /*
             * @brief Constructs the shader program
             */
            ShaderProgram();

            /**
             * @brief Destructs the shader program
             */
            ~ShaderProgram();

            /**
             * @brief Attaches the given shader to the program
             * @param shader The shader to attach
             * @return       This shader-program, in order to easily attach multiple shaders
             */
            ShaderProgram& attach(const id::graphics::Shader& shader);

            /**
             * @brief Links the shader program
             * @return       Whether the linking was successful
             * @retval true  The program was successfully linked
             * @retval false The linking of the program resulted in an error
             */
            bool link();

            /**
             * @brief Resets the program ("un-attaches" all shaders)
             */
            void reset();

            /**
             * @brief Uses the shader program
             * @return Whether it succeeded or not
             */
            bool use() const;

            /**
             * @brief Returns the ID of the OpenGL-program
             * @return The ID
             */
            const unsigned int getID() const;

            void setFloat(const std::string& name, float value);
            void setInteger(const std::string& name, int value);
            void setVector2f(const std::string& name, float x, float y);
            void setVector2f(const std::string& name, const id::graphics::Vector2f& value);
            void setVector3f(const std::string& name, float x, float y, float z);
            void setVector3f(const std::string& name, const id::graphics::Vector3f& value);
            void setVector4f(const std::string& name, float x, float y, float z, float w);
            void setVector4f(const std::string& name, const id::graphics::Vector4f& value);
            void setMatrix4(const std::string& name, const glm::mat4& matrix);

        private:
            /* data */
            bool m_created, m_linked;
            std::string m_name;
            unsigned int m_program;
        };
    } /* graphics */
} /* id */
