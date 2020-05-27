/**
 * @file common/loaders/Loader.hpp
 * @brief Defines the Loader-class
 */
#pragma once

#include <string>
#include <fstream>

namespace id {
    /**
     * @brief Contains everything loader-related
     */
    namespace loaders {
        /**
         * @brief The base class for all loaders
         */
        class Loader {
        public:
            /**
             * @brief Destructs the Loader
             */
            virtual ~Loader() { /* do nothing */ };

            /**
             * @brief Loads data from a file into the Loader
             * @param  filepath The filepath to load from
             * @return          Whether the loading was successful
             * @note This only loads the file into memory and passes it to `loadFromMemory()`
             */
            virtual bool loadFromFile(const std::string& filepath);

            /**
             * @brief  Loads data from a buffer into the Loader
             * @param  buffer The buffer to load from
             * @return        Whether the loading was successful
             * @note Interpreting the loaded data is up to the implementations
             */
            virtual bool loadFromMemory(const std::string& buffer) = 0;

            /**
             * @brief Unloads any data currently inside the Loader
             */
            virtual void unload() = 0;
        };
    } /* loaders */
} /* id */
