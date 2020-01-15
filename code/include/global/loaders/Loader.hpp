#pragma once

#include <string>

namespace id {
    namespace loaders {
        class Loader {
        public:
            virtual bool load(const std::string& buffer) = 0;
        };
    } /* loaders */
} /* id */
