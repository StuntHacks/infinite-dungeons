#pragma once

namespace id {
    class Application {
    public:
        static bool isRunning();
        static void exit();

    private:
        Application() {}; // prevent instance-creation

        /* data */
        static inline bool m_isRunning = true;
    };
} /* id */
