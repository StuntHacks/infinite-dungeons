#include "common/graphics/Quaternion.hpp"

namespace id {
    namespace graphics {
        Quaternion::Quaternion(float x, float y, float z, float w) :
        m_x(x),
        m_y(y),
        m_z(z),
        m_w(w) {
            normalize();
        }

        float Quaternion::getX() {
            return m_x;
        }

        float Quaternion::getY() {
            return m_y;
        }

        float Quaternion::getZ() {
            return m_z;
        }

        float Quaternion::getW() {
            return m_w;
        }

        void Quaternion::normalize() {
            float mag = static_cast<float>(sqrt(m_w * m_w + m_x * m_x + m_y * m_y + m_z * m_z));
            m_w /= mag;
            m_x /= mag;
            m_y /= mag;
            m_z /= mag;
        }

        glm::mat4 Quaternion::toMatrix() {
            glm::mat4 matrix;
            const float xy = m_x * m_y;
            const float xz = m_x * m_z;
            const float xw = m_x * m_w;
            const float yz = m_y * m_z;
            const float yw = m_y * m_w;
            const float zw = m_z * m_w;
            const float xSquared = m_x * m_x;
            const float ySquared = m_y * m_y;
            const float zSquared = m_z * m_z;
            matrix[0][0] = 1.0 - 2.0 * (ySquared + zSquared);
            matrix[0][1] = 2.0 * (xy - zw);
            matrix[0][2] = 2.0 * (xz + yw);
            matrix[0][3] = 0.0;
            matrix[1][0] = 2.0 * (xy + zw);
            matrix[1][1] = 1.0 - 2.0 * (xSquared + zSquared);
            matrix[1][2] = 2.0 * (yz - xw);
            matrix[1][3] = 0.0;
            matrix[2][0] = 2.0 * (xz - yw);
            matrix[2][1] = 2.0 * (yz + xw);
            matrix[2][2] = 1.0 - 2.0 * (xSquared + ySquared);
            matrix[2][3] = 0.0;
            matrix[3][0] = 0.0;
            matrix[3][1] = 0.0;
            matrix[3][2] = 0.0;
            matrix[3][3] = 1.0;
            return matrix;
        }

        id::graphics::Quaternion& Quaternion::fromMatrix(glm::mat4 rotationMatrix) {
            float diagonal = rotationMatrix[0][0] + rotationMatrix[1][1] + rotationMatrix[2][2];
            if (diagonal > 0.0) {
                float w4 = static_cast<float>(sqrt(diagonal + 1.0f) * 2.0f);
                m_w = w4 / 4.0f;
                m_x = (rotationMatrix[2][1] - rotationMatrix[1][2]) / w4;
                m_y = (rotationMatrix[0][2] - rotationMatrix[2][0]) / w4;
                m_z = (rotationMatrix[1][0] - rotationMatrix[0][1]) / w4;
            } else if ((rotationMatrix[0][0] > rotationMatrix[1][1]) && (rotationMatrix[0][0] > rotationMatrix[2][2])) {
                float x4 = static_cast<float>(sqrt(1.0f + rotationMatrix[0][0] - rotationMatrix[1][1] - rotationMatrix[2][2]) * 2.0f);
                m_w = (rotationMatrix[2][1] - rotationMatrix[1][2]) / x4;
                m_x = x4 / 4.0f;
                m_y = (rotationMatrix[0][1] + rotationMatrix[1][0]) / x4;
                m_z = (rotationMatrix[0][2] + rotationMatrix[2][0]) / x4;
            } else if (rotationMatrix[1][1] > rotationMatrix[2][2]) {
                float y4 = static_cast<float>(sqrt(1.0f + rotationMatrix[1][1] - rotationMatrix[0][0] - rotationMatrix[2][2]) * 2.0f);
                m_w = (rotationMatrix[0][2] - rotationMatrix[2][0]) / y4;
                m_x = (rotationMatrix[0][1] + rotationMatrix[1][0]) / y4;
                m_y = y4 / 4.0f;
                m_z = (rotationMatrix[1][2] + rotationMatrix[2][1]) / y4;
            } else {
                float z4 = static_cast<float>(sqrt(1.0f + rotationMatrix[2][2] - rotationMatrix[0][0] - rotationMatrix[1][1]) * 2.0f);
                m_w = (rotationMatrix[1][0] - rotationMatrix[0][1]) / z4;
                m_x = (rotationMatrix[0][2] + rotationMatrix[2][0]) / z4;
                m_y = (rotationMatrix[1][2] + rotationMatrix[2][1]) / z4;
                m_z = z4 / 4.0f;
            }

            return *this;
        }

        id::graphics::Quaternion Quaternion::getInterpolation(id::graphics::Quaternion destination, float progress) {
            Quaternion result(0.0, 0.0, 0.0, 1.0);
            float dot = m_w * destination.m_w + m_x * destination.m_x + m_y * destination.m_y + m_z * destination.m_z;

            if (progress < 0.0f) {
                progress = 0.0f;
            } else if (progress > 1.0f) {
                progress = 1.0f;
            }

            float remaining = 1.0f - progress;

            if (dot < 0.0f) {
                result.m_w = remaining * m_w + progress * -destination.m_w;
                result.m_x = remaining * m_x + progress * -destination.m_x;
                result.m_y = remaining * m_y + progress * -destination.m_y;
                result.m_z = remaining * m_z + progress * -destination.m_z;
            } else {
                result.m_w = remaining * m_w + progress * destination.m_w;
                result.m_x = remaining * m_x + progress * destination.m_x;
                result.m_y = remaining * m_y + progress * destination.m_y;
                result.m_z = remaining * m_z + progress * destination.m_z;
            }

            result.normalize();
            return result;
        }
    } /* graphics */
} /* id */
