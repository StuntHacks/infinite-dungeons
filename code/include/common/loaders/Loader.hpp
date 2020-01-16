/**
 * @file common/loaders/Loader.hpp
 * @brief Defines the Loader-class
 */
#pragma once

#include <string>

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
             * @brief  Loads data from a buffer into the Loader
             * @param  buffer The buffer to load from
             * @return        Whether the loading was successful
             * @note Interpreting the loaded data is up to the implementations
             */
            virtual bool load(const std::string& buffer) = 0;
        };
    } /* loaders */
} /* id */
