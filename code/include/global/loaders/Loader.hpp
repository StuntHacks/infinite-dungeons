#pragma once

#include <string>

namespace ta {
    namespace loaders {
        class Loader {
        public:
            virtual bool load(const std::string& buffer) = 0;
        };
    } /* loaders */
} /* ta */
