/**
 * @file common/Mutex.hpp
 * @brief Defines the Mutex class
 */
#pragma once

#ifdef __SWITCH__
    #include <sys/lock.h>
#else
    #ifdef __PC__
        #include <mutex>
    #endif
#endif

namespace id {
    /**
     * @brief A mutex
     */
    class Mutex {
    public:
        /**
         * @brief Creates the mutex
         */
        Mutex();

        /**
         * @brief Destructor
         *
         * This automatically unlocks the mutex
         */
        ~Mutex();

        /**
         * @brief Locks the mutex
         */
        void lock();

        /**
         * @brief Unlocks the mutex
         */
        void unlock();

    private:
        /* data */
        #ifdef __SWITCH__
            _LOCK_RECURSIVE_T m_mutex;
        #else
            #ifdef __PC__
                std::recursive_mutex m_mutex;
            #endif
        #endif
    };
} /* id */
