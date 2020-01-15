#pragma once

#include <string>
#include <vector>
#include "Loader.hpp"
#include "global/graphics/drawables/Model.hpp"

namespace id {
    namespace loaders {
        class ModelLoader: public Loader {
        public:
            virtual std::vector<id::graphics::Model::Vertex> getGeometry() {
                return m_geometry;
            };

            virtual std::vector<id::graphics::Texture> getTextures() {
                return m_textures;
            };

            virtual std::vector<id::graphics::Model::DrawBatch> getDrawBatches() {
                return m_drawBatches;
            };

        protected:
            /* data */
            std::vector<id::graphics::Model::Vertex> m_geometry;
            std::vector<id::graphics::Texture> m_textures;
            std::vector<id::graphics::Model::DrawBatch> m_drawBatches;
        };
    } /* loaders */
} /* id */
