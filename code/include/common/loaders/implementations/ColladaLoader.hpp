#pragma once

#include "common/loaders/ModelLoader.hpp"

namespace id {
    namespace loaders {
        class ColladaLoader: public ModelLoader {
        public:
            bool loadFromMemory(const std::string& buffer);
        };
    } /* loaders */
} /* id */
