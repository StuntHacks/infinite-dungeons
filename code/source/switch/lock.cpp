#include "switch/lock.hpp"

namespace id {
    Lock::Lock(Mutex& t_mutex) :
            m_mutex(t_mutex) {
        m_mutex.lock();
    }

    Lock::~Lock() {
        m_mutex.unlock();
    }
} /* id */
