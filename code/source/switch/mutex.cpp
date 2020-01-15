#include <switch.h>
#include "switch/mutex.hpp"

namespace id {
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
} /* id */
