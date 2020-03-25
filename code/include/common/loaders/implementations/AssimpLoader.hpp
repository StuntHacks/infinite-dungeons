#pragma once

#include "common/loaders/ModelLoader.hpp"
#include <assimp/Importer.hpp>

namespace id {
    namespace loaders {
        class AssimpLoader: public ModelLoader {
        public:
            // bool loadFromFile(const std::string& filepath);
            bool loadFromMemory(const std::string& buffer);

        protected:
            Assimp::Importer m_importer;
        };
    } /* loaders */
} /* id */
