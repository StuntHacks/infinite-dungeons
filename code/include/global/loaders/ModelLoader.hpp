#pragma once

#include <string>
#include <vector>
#include "Loader.hpp"
#include "global/graphics/drawables/Model.hpp"

namespace ta {
    namespace loaders {
        class ModelLoader: public Loader {
        public:
            virtual std::vector<ta::graphics::Model::Vertex> getGeometry() {
                return m_geometry;
            };

            virtual std::vector<ta::graphics::Texture> getTextures() {
                return m_textures;
            };

            virtual std::vector<ta::graphics::Model::DrawBatch> getDrawBatches() {
                return m_drawBatches;
            };

        protected:
            /* data */
            std::vector<ta::graphics::Model::Vertex> m_geometry;
            std::vector<ta::graphics::Texture> m_textures;
            std::vector<ta::graphics::Model::DrawBatch> m_drawBatches;
        };
    } /* loaders */
} /* ta */
