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
             * @brief Destructs the ModelLoader
             */
            virtual ~ModelLoader();

            /**
             * @brief Returns the geometry of the loaded model
             * @return A vector containing all vertices
             */
            virtual std::vector<id::graphics::Model::Vertex> getGeometry();

            /**
             * @brief Returns the textures used by the loaded model
             * @return A vector containing all textures used by the model
             */
            virtual std::vector<id::graphics::Texture> getTextures();

            /**
             * @brief Returns the prepared DrawBatches for the loaded model
             * @returns A vector containing the DrawBatches for the model
             */
            virtual std::vector<id::graphics::Model::DrawBatch> getDrawBatches();

            /**
             * @brief Unloads any data currently inside the Loader
             */
            virtual void unload();

        protected:
            /* data */
            std::vector<id::graphics::Model::Vertex> m_geometry;
            std::vector<id::graphics::Texture> m_textures;
            std::vector<id::graphics::Model::DrawBatch> m_drawBatches;
        };
    } /* loaders */
} /* id */
