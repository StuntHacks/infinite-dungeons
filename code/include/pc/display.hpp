#ifdef __PC__
/**
 * @file pc/display.hpp
 * @brief Defines the Display namespace
 */
#pragma once

#include "opengl.hpp"

namespace id {
    /**
     * @brief Contains data about the application-window
     */
    namespace Display {
        static inline float getScreenWidth() {
            GLint viewport[4];
            glGetIntegerv(GL_VIEWPORT, viewport);
            return static_cast<float>(viewport[2]);
        }

        static inline float getScreenHeight() {
            GLint viewport[4];
            glGetIntegerv(GL_VIEWPORT, viewport);
            return static_cast<float>(viewport[3]);
        }
    } /* Display */
} /* id */
#endif
