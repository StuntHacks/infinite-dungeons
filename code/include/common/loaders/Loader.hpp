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

            virtual bool loadFromFile(const std::string& filepath) {
                std::ifstream file(filepath);
                std::string buffer((std::istreambuf_iterator<char>(file)),
                                    std::istreambuf_iterator<char>());

                return loadFromMemory(buffer);
            }

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
