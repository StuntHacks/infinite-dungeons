#pragma once

#include <fstream>
#include <streambuf>
#include <string>
#include <vector>
#include "opengl.hpp"
#include "global/graphics/Drawable.hpp"
#include "global/graphics/Texture.hpp"
#include "global/graphics/Vertex.hpp"

namespace ta {
    namespace loaders {
        class ModelLoader;
    } /* loaders */

    namespace graphics {
        class Model: public Drawable {
        friend class ta::loaders::ModelLoader;
        public:
            struct Vertex {
                Vector3f position;
                Vector2f texCoords;
                Vector3f normals;
                Vector4i joints;
                Vector4f weights;
            };

            struct Material {
                ta::graphics::Vector3f ambient;
                ta::graphics::Vector3f diffuse;
                ta::graphics::Vector3f specular;
                float shininess;
            };

            class Joint {
            public:
                Joint(int id, const std::string& name, glm::mat4 localBindTransform);

                std::vector<ta::graphics::Model::Joint>& getChildren();
                void addChildren(ta::graphics::Model::Joint child);

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
                std::vector<ta::graphics::Model::Joint> m_children;
            };

            Model();
            virtual ~Model();

            template <class LoaderType>
            bool loadFromFile(const std::string& filepath) {
                static_assert(std::is_base_of<ta::loaders::ModelLoader, LoaderType>::value, "Wrong Loader-type provided. Make sure you use an implementation of ModelLoader.");

                std::ifstream file(filepath);
                std::string buffer((std::istreambuf_iterator<char>(file)),
                                    std::istreambuf_iterator<char>());

                return _load<LoaderType>(buffer);
            };

            template <class LoaderType>
            bool loadFromMemory(const std::string& buffer) {
                static_assert(std::is_base_of<ta::loaders::ModelLoader, LoaderType>::value, "Wrong Loader-type provided. Make sure you use an implementation of ModelLoader.");

                return _load<LoaderType>(buffer);
            };

            virtual void draw(ta::graphics::Renderer& renderer, bool);

        protected:
            struct DrawBatch {
                /* data */
                int textureID;
                unsigned int vao, vbo;
                Material material;
            };

            template <class LoaderType>
            bool _load(const std::string& buffer) {
                LoaderType loader;

                if (!loader.load(buffer)) {
                    // log...
                    return false;
                }

                std::vector<ta::graphics::Model::Vertex> geometry = loader.getGeometry();

                m_drawBatches.clear();
                m_drawBatches = loader.getDrawBatches();

                return true;
            };

        private:
            /* data */
            std::vector<ta::graphics::Model::DrawBatch> m_drawBatches;
        };
    } /* graphics */
} /* ta */
