#include "global/Application.hpp"
#include "switch/input.hpp"

#include <switch.h>

namespace ta {
    bool Application::isRunning() {
        ta::Input::scanInput();
        return m_isRunning && appletMainLoop();
    }

    void Application::exit() {
        m_isRunning = false;
    }
} /* ta */
