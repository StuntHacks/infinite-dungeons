#include "global/graphics/RenderTarget.hpp"

#include <glad/glad.h>

namespace ta {
    namespace graphics {
        RenderTarget::RenderTarget() {
            glGenFramebuffers(1, &m_framebuffer);
        }

        RenderTarget::~RenderTarget() {
            glDeleteFramebuffers(1, &m_framebuffer);
        }

        void RenderTarget::bind() {
            glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
        }
    } /* graphics */
} /* ta */
