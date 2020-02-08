#include "common/Application.hpp"
#include "common/graphics/Renderer.hpp"
#include "common/menu/TextBoxManager.hpp"
#include "switch/input.hpp"
#include "pc/input.hpp"

#ifdef __SWITCH__
    #include <switch.h>
#endif

namespace id {
    bool Application::isRunning() {
        #ifdef __SWITCH__
            id::Input::scanInput();
            id::menu::TextBoxManager::getInstance().update();
            return m_isRunning && appletMainLoop();
        #else
            #ifdef __PC__
                id::pc::Input::scanInput();
                id::menu::TextBoxManager::getInstance().update();
                return m_isRunning && !glfwWindowShouldClose(id::graphics::Renderer::getInstance().m_window);
            #endif
        #endif
    }

    void Application::exit() {
        m_isRunning = false;
    }
} /* id */
