#include "common/mutex.hpp"
#ifdef __SWITCH__
    #include <switch.h>
#endif

namespace id {
    #ifdef __SWITCH__
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
    #else
        #ifdef __PC__
            Mutex::Mutex() { /* do nothing */ }

            Mutex::~Mutex() {
                unlock();
            }

            void Mutex::lock() {
                m_mutex.lock();
            }

            void Mutex::unlock() {
                m_mutex.unlock();
            }
        #endif
    #endif

} /* id */
