#include "common/loaders/ModelLoader.hpp"

namespace id {
    namespace loaders {
        ModelLoader::~ModelLoader() { unload(); };

        std::vector<id::graphics::Model::Vertex> ModelLoader::getGeometry() {
            return m_geometry;
        };

        std::vector<id::graphics::Texture> ModelLoader::getTextures() {
            return m_textures;
        };

        std::vector<id::graphics::Model::DrawBatch> ModelLoader::getDrawBatches() {
            return m_drawBatches;
        };

        void ModelLoader::unload() {
            m_geometry.clear();
            m_textures.clear();
            m_drawBatches.clear();
        };
    } /* loaders */
} /* id */
