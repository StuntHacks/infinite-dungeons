#include "global/graphics/drawables/Model.hpp"

namespace ta {
    namespace graphics {
        Model::Model() { /* do nothing */ }

        Model::~Model() {

        }

        void Model::draw(ta::graphics::Renderer& renderer, bool) {

        }

        /* Model::Joint */
        Model::Joint::Joint(int id, const std::string& name, glm::mat4 localBindTransform) :
        m_id(id),
        m_name(name),
        m_localBindTransform(localBindTransform) { /* do nothing */ }

        std::vector<ta::graphics::Model::Joint>& Model::Joint::getChildren() {
            return m_children;
        }

        void Model::Joint::addChildren(ta::graphics::Model::Joint child) {
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

        // protected methods
        void Model::Joint::calculateInverseLocalBindTransform(glm::mat4 parentBindTransform) {
            glm::mat4 bindTransform = parentBindTransform * m_localBindTransform;
            m_inverseBindTransform = glm::inverse(bindTransform);

            for (auto& child: m_children) {
                child.calculateInverseLocalBindTransform(bindTransform);
            }
        }
    } /* graphics */
} /* ta */
