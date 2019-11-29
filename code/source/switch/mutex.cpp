#include <switch.h>
#include "switch/mutex.hpp"

namespace ta {
    Mutex::Mutex() {
        rmutexInit(&m_mutex);
    }

    Mutex::~Mutex() {
        rmutexUnlock(&m_mutex);
    }

    void Mutex::lock() {
        rmutexLock(&m_mutex);
    }

    void Mutex::unlock() {
        rmutexUnlock(&m_mutex);
    }
} /* ta */
