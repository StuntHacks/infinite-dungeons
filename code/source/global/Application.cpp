#include "global/Application.hpp"
#include "global/menu/TextBoxManager.hpp"
#include "switch/input.hpp"

#include <switch.h>

namespace id {
    bool Application::isRunning() {
        id::Input::scanInput();
        id::menu::TextBoxManager::getInstance().update();
        return m_isRunning && appletMainLoop();
    }

    void Application::exit() {
        m_isRunning = false;
    }
} /* id */
