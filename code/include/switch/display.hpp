#pragma once

#include <switch.h>

namespace ta {
    namespace Display {
        static inline float getScreenWidth() {
            return appletGetOperationMode() == AppletOperationMode_Handheld ? 1280 : 1920;
        }

        static inline float getScreenHeight() {
            return appletGetOperationMode() == AppletOperationMode_Handheld ? 720 : 1080;
        }
    } /* Display */
} /* ta */
