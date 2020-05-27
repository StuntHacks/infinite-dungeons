#pragma once

namespace id {
    namespace settings {
        static inline unsigned char TextSpeed = 3;
        #ifdef __SWITCH__
            static inline std::string DefaultFontPath = "romfs:/assets/fonts/Lato/Lato-Regular.ttf";
        #else
            #ifdef __PC__
                static inline std::string DefaultFontPath = "./romfs/assets/fonts/Lato/Lato-Regular.ttf";
            #endif
        #endif
    } /* Settings */
} /* id */
