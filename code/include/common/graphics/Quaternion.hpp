#pragma once

#include <cmath>
#include "opengl.hpp"

namespace id {
    namespace graphics {
        class Quaternion {
        public:
            Quaternion(float x, float y, float z, float w);
            void normalize();

            float getX();
            float getY();
            float getZ();
            float getW();

            glm::mat4 toMatrix();
            id::graphics::Quaternion& fromMatrix(glm::mat4 rotationMatrix);

            id::graphics::Quaternion getInterpolation(id::graphics::Quaternion destination, float progress);
        private:
            /* data */
            float m_x, m_y, m_z, m_w;
        };
    } /* graphics */
} /* id */
