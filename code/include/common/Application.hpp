/**
 * @file common/Application.hpp
 * @brief Defines the Application-class
 */
#pragma once

/**
 * @brief The main Infinite Dungeons namespace
 */
namespace id {
    /**
     * @brief Handles the main loop
     */
    class Application {
    public:
        /**
         * @brief Returns whether the app is still running, and calls loop-hooks
         * @return Whether the app is still running
         */
        static bool isRunning();

        /**
         * @brief Exits the app safely
         */
        static void exit();

    private:
        Application() {}; // prevent instance-creation

        /* data */
        static inline bool m_isRunning = true;
    };
} /* id */
