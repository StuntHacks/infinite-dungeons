/**
 * @file common/loaders/implementations/ImageLoader.hpp
 * @brief Defines the ImageLoader-class
 */
#pragma once

#include "common/loaders/TextureLoader.hpp"

namespace id {
    namespace loaders {
        /**
         * @brief Allows to load Textures from image-files
         */
        class ImageLoader: public TextureLoader {
        public:
            /**
             * @brief Loads a texture from memory using stb_image
             * @param  filepath The path to the file to load
             * @return          `true` of the loading succeeded, `false` otherwise
             */
            bool loadFromFile(const std::string& filepath);

            /**
             * @brief Loads a texture from memory using stb_image
             * @param  buffer The buffer to load from
             * @return        `true` of the loading succeeded, `false` otherwise
             */
            bool loadFromMemory(const std::string& buffer);

        private:
            bool _load(unsigned char* data, int width, int height, int nrChannels);
        };
    } /* loaders */
} /* id */
