#include "global/Application.hpp"
#include "global/menu/TextBoxManager.hpp"
#include "switch/input.hpp"

#include <switch.h>

namespace ta {
    bool Application::isRunning() {
        ta::Input::scanInput();
        ta::menu::TextBoxManager::getInstance().update();
        return m_isRunning && appletMainLoop();
    }

    void Application::exit() {
        m_isRunning = false;
    }
} /* ta */
