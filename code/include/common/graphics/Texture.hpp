/**
 * @file common/graphics/Texture.hpp
 * @brief Defines the Texture-class
 */
#pragma once

#include <string>
#include <algorithm>
#include "opengl.hpp"

namespace id {
    namespace graphics {
        /**
         * @brief Contains an OpenGl-texture, and provides loading-methods
         */
        class Texture {
        public:
            /**
             * @brief Constructor
             * @param autoDelete Whether the texture should automatically delete itself when the constructor is called
             */
            Texture(bool autoDelete = true);

            /**
             * @brief Constructs and loads a texture
             * @param filepath      The filepath
             * @param smoothTexture Whether to smooth the Texture
             * @param wrapS         The s-wrap of the texture
             * @param wrapT         The t-wrap of the texture
             * @param autoDelete    Whether the texture should automatically delete itself when the constructor is called
             */
            Texture(const std::string& filepath, bool smoothTexture = true, GLenum wrapS = GL_REPEAT, GLenum wrapT = GL_REPEAT, bool autoDelete = true);

            /**
             * @brief Destructs the Texture
             */
            virtual ~Texture();

            /**
             * @brief Loads a Texture from the filesystem
             * @param  filepath      The filepath
             * @param  smoothTexture Whether to smooth the Texture
             * @param  wrapS         The s-wrap of the texture
             * @param  wrapT         The t-wrap of the texture
             * @return               `true` if the loading succeeded, `false` otherwise
             */
            bool loadFromFile(const std::string& filepath, bool smoothTexture = true, GLenum wrapS = GL_REPEAT, GLenum wrapT = GL_REPEAT);

            /**
             * @brief Returns the OpenGL texture-id of the Texture
             * @return The texture-id
             */
            unsigned int getTexture();

            /**
             * @brief Returns the width of the texture
             * @return The width
             */
            unsigned int getWidth();

            /**
             * @brief Returns the height of the texture
             * @return The height
             */
            unsigned int getHeight();

            /**
             * @brief Returns whether the Texture should automatically delete itself
             * @return `true` if autoDelete is enabled, `false` otherwise
             */
            bool getAutoDelete();

            /**
             * @brief Sets whether the texture should automatically delete itself
             * @param autoDelete Whether to automatically delete or not
             */
            void setAutoDelete(bool autoDelete);

            /**
             * @brief Deletes the texture
             */
            void deleteTexture();

            /**
             * @brief Binds the texture
             */
            void bind();

        private:
            /* data */
            unsigned int m_texture, m_width, m_height;
            bool m_autoDelete;
        };
    } /* graphics */
} /* id */
