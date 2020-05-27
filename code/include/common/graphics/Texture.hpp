/**
 * @file common/graphics/Texture.hpp
 * @brief Defines the Texture-class
 */
#pragma once

#include <string>
#include <algorithm>
#include "opengl.hpp"
#include "common/AutoDeletable.hpp"
#include "common/Console.hpp"

namespace id {
    namespace loaders {
        class TextureLoader;
    } /* loaders */

    namespace graphics {
        /**
         * @brief Contains an OpenGl-texture, and provides loading-methods
         */
        class Texture: public id::AutoDeletable {
        public:
            /**
             * @brief Constructor
             * @param autoDelete Whether the texture should automatically delete itself when the constructor is called
             */
            Texture(bool autoDelete = true);

            /**
             * @brief Destructs the Texture
             */
            virtual ~Texture();

            /**
             * @brief Returns whether the texture is loaded or not
             * @return `true` if the texture is loaded, `false` otherwise
             */
            bool isLoaded();

            template <class LoaderType>
            bool loadFromFile(const std::string& filepath) {
                static_assert(std::is_base_of<id::loaders::TextureLoader, LoaderType>::value, "Wrong Loader-type provided. Make sure you use an implementation of TextureLoader.");

                LoaderType loader;
                if (!loader.loadFromFile(filepath)) {
                    return false;
                }

                _load<LoaderType>(loader);
                return true;
            };

            template <class LoaderType>
            bool loadFromMemory(const std::string& buffer) {
                static_assert(std::is_base_of<id::loaders::TextureLoader, LoaderType>::value, "Wrong Loader-type provided. Make sure you use an implementation of TextureLoader.");

                LoaderType loader;
                if (!loader.loadFromMemory(buffer)) {
                    return false;
                }

                 _load<LoaderType>(loader);
                 return true;
            };

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
             * @brief Deletes the texture
             */
            void deleteThis();

            /**
             * @brief Binds the texture
             */
            void bind();

        protected:
            template <class LoaderType>
            void _load(LoaderType loader) {
                m_texture = loader.getID();
                m_width = loader.getWidth();
                m_height = loader.getHeight();
            };

        private:
            /* data */
            unsigned int m_texture, m_width, m_height;
        };
    } /* graphics */
} /* id */
