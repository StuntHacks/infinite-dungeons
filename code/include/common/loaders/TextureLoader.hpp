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
             * @brief Default constructor
             */
            TextureLoader();

            /**
             * @brief Destructs the TextureLoader
             */
            virtual ~TextureLoader();

            /**
             * @brief Returns the width of the loaded texture
             * @return The width
             */
            virtual int getWidth();

            /**
             * @brief Returns the height of the loaded texture
             * @return The height
             */
            virtual int getHeight();

            /**
             * @brief Returns the id of the loaded texture
             * @return The id
             */
            virtual int getID();

            /**
             * @brief Unloads any data currently inside the Loader
             */
            virtual void unload();

        protected:
            /* data */
            unsigned int m_width, m_height, m_texture;
        };
    } /* loaders */
} /* id */
