/**
 * @file mutex.hpp
 * @brief Defines the Mutex class
 */
#pragma once

#include <sys/lock.h>

namespace ta {
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
        _LOCK_RECURSIVE_T m_mutex;
    };
} /* ta */
