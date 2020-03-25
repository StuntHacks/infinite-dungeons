#pragma once

#include <fstream>
#include <streambuf>
#include <string>
#include <vector>
#include "opengl.hpp"
#include "common/graphics/Drawable.hpp"
#include "common/graphics/Texture.hpp"
#include "common/graphics/Vertex.hpp"

namespace id {
    namespace loaders {
        class ModelLoader;
    } /* loaders */

    namespace graphics {
        class Model: public Drawable {
        friend class id::loaders::ModelLoader;
        public:
            struct Vertex {
                Vector3f position;
                Vector2f texCoords;
                Vector3f normals;
                Vector4i joints;
                Vector4f weights;
            };

            struct Material {
                id::graphics::Vector3f ambient;
                id::graphics::Vector3f diffuse;
                id::graphics::Vector3f specular;
                float shininess;
            };

            class Joint {
            public:
                Joint(int id, const std::string& name, glm::mat4 localBindTransform);

                std::vector<id::graphics::Model::Joint>& getChildren();
                void addChildren(id::graphics::Model::Joint child);

                void setLocalAnimationTransform(glm::mat4 transform);
                glm::mat4 getLocalAnimationTransform() const;
                glm::mat4 getLocalBindTransform() const;
                glm::mat4 getInverseLocalBindTransform() const;

            protected:
                void calculateInverseLocalBindTransform(glm::mat4 parentBindTransform);

            private:
                /* data */
                int m_id;
                std::string m_name;
                glm::mat4 m_localBindTransform, m_inverseBindTransform, m_animationTransform;
                std::vector<id::graphics::Model::Joint> m_children;
            };

            Model();
            virtual ~Model();

            template <class LoaderType>
            bool loadFromFile(const std::string& filepath) {
                static_assert(std::is_base_of<id::loaders::ModelLoader, LoaderType>::value, "Wrong Loader-type provided. Make sure you use an implementation of ModelLoader.");

                LoaderType loader;
                if (!loader.loadFromFile(filepath)) {
                    return false;
                }

                return _load<LoaderType>(loader);
            };

            template <class LoaderType>
            bool loadFromMemory(const std::string& buffer) {
                static_assert(std::is_base_of<id::loaders::ModelLoader, LoaderType>::value, "Wrong Loader-type provided. Make sure you use an implementation of ModelLoader.");

                LoaderType loader;
                if (!loader.loadFromMemory(buffer)) {
                    return false;
                }

                return _load<LoaderType>(loader);
            };

            virtual void draw(id::graphics::Renderer& renderer, bool);

        protected:
            struct DrawBatch {
                /* data */
                int textureID;
                unsigned int vao, vbo;
                Material material;
            };

            template <class LoaderType>
            bool _load(LoaderType loader) {
                std::vector<id::graphics::Model::Vertex> geometry = loader.getGeometry();

                m_drawBatches.clear();
                m_drawBatches = loader.getDrawBatches();

                return true;
            };

        private:
            /* data */
            std::vector<id::graphics::Model::DrawBatch> m_drawBatches;
        };
    } /* graphics */
} /* id */
