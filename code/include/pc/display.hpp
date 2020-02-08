#ifdef __PC__
/**
 * @file pc/lock.hpp
 * @brief Defines the Display namespace
 */
#pragma once

namespace id {
    /**
     * @brief Contains everything specific to PC-builds
     */
    namespace pc {
        /**
         * @brief Contains data about the application-window
         */
        namespace Display {
            static inline float getScreenWidth() {
                return 1920;
            }

            static inline float getScreenHeight() {
                return 1080;
            }
        } /* Display */
    } /* pc */
} /* id */
#endif
