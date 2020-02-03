/**
 * @file common/Lock.hpp
 * @brief Defines the Lock class
 */
#pragma once

#include "Mutex.hpp"

namespace id {
    class Mutex;

    /**
     * @brief Used to automatically and easily lock and unlock mutexes based on scope
     */
    class Lock {
    public:
        /**
         * @brief Creates the lock
         * @param mutex The mutex to lock
         */
        Lock(Mutex& mutex);

        /**
         * @brief Destructs the lock
         * @note This automatically unlocks it's mutex
         */
        ~Lock();

    private:
        /* data */
        Mutex m_mutex;
    };
} /* id */
