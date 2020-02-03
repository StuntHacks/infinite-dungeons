/**
 * @file common/loaders/TextureLoader.hpp
 * @brief Defines the TextureLoader-class
 */
#pragma once

#include <string>
#include <vector>
#include "Loader.hpp"
#include "common/graphics/Texture.hpp"

namespace id {
    namespace loaders {
        /**
         * @brief Loads a Texture
         */
        class TextureLoader: public Loader {
        public:
            /**
             * @brief Destructs the TextureLoader
             */
            virtual ~TextureLoader() { unload(); };

            /**
             * @brief Returns the width of the loaded texture
             * @return The width
             */
            virtual int getWidth() {
                return m_width;
            }

            /**
             * @brief Returns the height of the loaded texture
             * @return The height
             */
            virtual int getHeight() {
                return m_height;
            }

            /**
             * @brief Returns the id of the loaded texture
             * @return The id
             */
            virtual int getID() {
                return m_texture;
            }

            /**
             * @brief Unloads any data currently inside the Loader
             */
            virtual void unload() {
                m_texture = 0;
                m_width = 0;
                m_height = 0;
            };

        protected:
            /* data */
            unsigned int m_width, m_height, m_texture;
        };
    } /* loaders */
} /* id */
