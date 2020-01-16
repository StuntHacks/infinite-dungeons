/**
 * @file common/loaders/ModelLoader.hpp
 * @brief Defines the ModelLoader-class
 */
#pragma once

#include <string>
#include <vector>
#include "Loader.hpp"
#include "common/graphics/drawables/Model.hpp"

namespace id {
    namespace loaders {
        /**
         * @brief Loads a 3D model
         */
        class ModelLoader: public Loader {
        public:
            /**
             * @brief Returns the geometry of the loaded model
             * @return A vector containing all vertices
             */
            virtual std::vector<id::graphics::Model::Vertex> getGeometry() {
                return m_geometry;
            };

            /**
             * @brief Returns the textures used by the loaded model
             * @return A vector containing all textures used by the model
             */
            virtual std::vector<id::graphics::Texture&> getTextures() {
                return m_textures;
            };

            /**
             * @brief Returns the prepared DrawBatches for the loaded model
             * @returns A vector containing the DrawBatches for the model
             */
            virtual std::vector<id::graphics::Model::DrawBatch> getDrawBatches() {
                return m_drawBatches;
            };

        protected:
            /* data */
            std::vector<id::graphics::Model::Vertex> m_geometry;
            std::vector<id::graphics::Texture&> m_textures;
            std::vector<id::graphics::Model::DrawBatch> m_drawBatches;
        };
    } /* loaders */
} /* id */
