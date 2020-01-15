#pragma once

#include "mutex.hpp"

namespace id {
    class Mutex;

    /**
     * @brief Used to automatically and easily lock and unlock mutexes based on scope
     */
    class Lock {
    public:
        /**
         * @brief Creates the lock
         * @param t_mutex The mutex to lock
         */
        Lock(Mutex& t_mutex);

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
