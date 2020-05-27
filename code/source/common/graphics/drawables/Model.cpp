#include "common/graphics/drawables/Model.hpp"

namespace id {
    namespace graphics {
        Model::Model(bool autoDelete) {
            setAutoDelete(autoDelete);
        }

        Model::~Model() {
            if (m_autoDelete) {
                deleteThis();
            }
        }

        bool Model::isLoaded() {
            return false;
        }

        void Model::draw(id::graphics::Renderer& renderer, bool) {

        }

        /* Model::Joint */
        Model::Joint::Joint(int id, const std::string& name, glm::mat4 localBindTransform) :
        m_id(id),
        m_name(name),
        m_localBindTransform(localBindTransform) { /* do nothing */ }

        std::vector<id::graphics::Model::Joint>& Model::Joint::getChildren() {
            return m_children;
        }

        void Model::Joint::addChildren(id::graphics::Model::Joint child) {
            m_children.push_back(child);
        }

        void Model::Joint::setLocalAnimationTransform(glm::mat4 transform) {
            m_animationTransform = transform;
        }

        glm::mat4 Model::Joint::getLocalAnimationTransform() const {
            return m_animationTransform;
        }

        glm::mat4 Model::Joint::getLocalBindTransform() const {
            return m_localBindTransform;
        }

        glm::mat4 Model::Joint::getInverseLocalBindTransform() const {
            return m_inverseBindTransform;
        }

        void Model::deleteThis() {
            if (isLoaded()) {
            }
        }

        // protected methods
        void Model::Joint::calculateInverseLocalBindTransform(glm::mat4 parentBindTransform) {
            glm::mat4 bindTransform = parentBindTransform * m_localBindTransform;
            m_inverseBindTransform = glm::inverse(bindTransform);

            for (auto& child: m_children) {
                child.calculateInverseLocalBindTransform(bindTransform);
            }
        }
    } /* graphics */
} /* id */
