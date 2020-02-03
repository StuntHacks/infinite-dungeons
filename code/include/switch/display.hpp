#ifdef __SWITCH__
/**
 * @file switch/lock.hpp
 * @brief Defines the Display namespace
 */
#pragma once

#include <switch.h>

namespace id {
    /**
     * @brief Contains data about the switch-display
     */
    namespace Display {
        static inline float getScreenWidth() {
            return appletGetOperationMode() == AppletOperationMode_Handheld ? 1280 : 1920;
        }

        static inline float getScreenHeight() {
            return appletGetOperationMode() == AppletOperationMode_Handheld ? 720 : 1080;
        }
    } /* Display */
} /* id */
#endif
