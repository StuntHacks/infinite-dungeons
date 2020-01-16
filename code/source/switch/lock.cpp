#include "switch/lock.hpp"

namespace id {
    Lock::Lock(Mutex& mutex) :
            m_mutex(mutex) {
        m_mutex.lock();
    }

    Lock::~Lock() {
        m_mutex.unlock();
    }
} /* id */
