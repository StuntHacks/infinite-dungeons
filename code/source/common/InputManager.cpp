#include <cmath>
#include "common/InputManager.hpp"
#include "common/Application.hpp"
#include "common/graphics/Renderer.hpp"
#include "common/events/InputEvent.hpp"
#include "common/events/KeyPressEvent.hpp"
#include "common/events/ButtonPressEvent.hpp"
#include "common/events/TextEvent.hpp"
#include "switch/input.hpp"

namespace id {
    id::events::PressEvent::State InputManager::getCachedInputState(const std::string& id, bool preferButtons) {
        #if defined(__SWITCH__)
            // TODO
        #elif defined(__PC__)
            using namespace id::events;

            if (m_keyBindings.count(id) != 0 && !preferButtons) {
                return static_cast<id::events::PressEvent::State>(glfwGetKey(&id::graphics::Renderer::getInstance().getGLFWWindow(), static_cast<int>(m_keyBindings[id])));
            } else if (m_buttonBindings.count(id) != 0) {
                return m_cachedButtonStates[m_buttonBindings[id]];
            }

            return PressEvent::State::Unknown;
        #endif
    }

    id::graphics::Vector2f InputManager::getJoystickCartesian(Joystick stick) {
        GLFWgamepadstate state;

        if (glfwGetGamepadState(GLFW_JOYSTICK_1, &state)) {
            float x = state.axes[static_cast<int>(stick)];

            if (x < 0.1f && x > -0.1f) {
                x = 0.0f;

            }

            float y = state.axes[static_cast<int>(stick) + 1];

            if (y < 0.1f && y > -0.1f) {
                y = 0.0f;
            }

            return id::graphics::Vector2f({ x, y });
        }

        return id::graphics::Vector2f({ 0.0f, 0.0f });
    }

    id::graphics::Vector2f InputManager::getJoystickPolar(Joystick stick) {
        id::graphics::Vector2f position = getJoystickCartesian(stick);
        float angle;

        if (position.u == 0 && position.v == 0) {
            angle = 0.0f;
        } else {
            angle = 360.0f - (180.0f - (glm::degrees(atan2(0.0f - position.v, 0.0f - position.u)) * -1.0f));
        }

        return id::graphics::Vector2f({ angle, sqrt(pow(abs(position.u), 2) + pow(abs(position.v), 2)) });
    }

    void InputManager::bindInput(const std::string& id, id::InputManager::Key key) {
        unbindKeyInput(id);
        m_keyBindings[id] = key;
        m_keys[key].push_back(id);
    }

    void InputManager::bindInput(const std::string& id, id::InputManager::Button button) {
        unbindButtonInput(id);
        m_buttonBindings[id] = button;
        m_buttons[button].push_back(id);
    }

    void InputManager::unbindInput(const std::string& id) {
        unbindKeyInput(id);
        unbindButtonInput(id);
    }

    bool InputManager::unbindKeyInput(const std::string& id) {
        if (m_keyBindings.count(id) != 0) {
            std::vector<std::string>::iterator it = std::find(m_keys[m_keyBindings[id]].begin(), m_keys[m_keyBindings[id]].end(), id);

            if (it != m_keys[m_keyBindings[id]].end()) {
                m_keys[m_keyBindings[id]].erase(it);
            }

            m_keyBindings.erase(id);

            return true;
        }

        return false;
    }

    bool InputManager::unbindButtonInput(const std::string& id) {
        if (m_buttonBindings.count(id) != 0) {
            std::vector<std::string>::iterator it = std::find(m_buttons[m_buttonBindings[id]].begin(), m_buttons[m_buttonBindings[id]].end(), id);

            if (it != m_buttons[m_buttonBindings[id]].end()) {
                m_buttons[m_buttonBindings[id]].erase(it);
            }

            m_buttonBindings.erase(id);

            return true;
        }

        return false;
    }

    void InputManager::clearInputs() {
        m_keys.clear();
        m_keyBindings.clear();
        clearCallbacks();
    }

    const std::string InputManager::registerCallback(const std::string& input, std::function<void(id::Event&)> callback) {
        return id::EventDispatcher::registerCallback(input, callback);
    }

    #if defined(__PC__)
        // protected methods
        void InputManager::_keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
            id::events::KeyPressEvent keyEvt(key, static_cast<id::events::PressEvent::State>(action));
            dispatch(keyEvt);

            if (m_keys.count(static_cast<id::InputManager::Key>(key)) != 0) {
                for (auto& input: m_keys[static_cast<id::InputManager::Key>(key)]) {
                    id::events::InputEvent inputEvt(input, static_cast<id::events::PressEvent::State>(action));
                    dispatch(inputEvt);
                }
            }
        }

        void InputManager::_characterCallback(GLFWwindow* window, unsigned int codepoint) {
            id::events::TextEvent evt(static_cast<wchar_t>(codepoint));
            dispatch(evt);
        }

        void InputManager::_scanCallback() {
            GLFWgamepadstate state;
            m_cachedButtonStates.clear();

            if (glfwGetGamepadState(GLFW_JOYSTICK_1, &state)) {
                for (int buttonId = 0; buttonId < static_cast<int>(Button::Last); ++buttonId) {
                    if (state.buttons[buttonId]) {
                        id::events::ButtonPressEvent buttonEvt(buttonId, static_cast<id::events::PressEvent::State>(state.buttons[buttonId]));
                        dispatch(buttonEvt);

                        m_cachedButtonStates[static_cast<Button>(buttonId)] = static_cast<id::events::PressEvent::State>(state.buttons[buttonId]);

                        if (m_buttons.count(static_cast<id::InputManager::Button>(buttonId)) != 0) {
                            for (auto& input: m_buttons[static_cast<id::InputManager::Button>(buttonId)]) {
                                id::events::InputEvent inputEvt(input, static_cast<id::events::PressEvent::State>(state.buttons[buttonId]));
                                dispatch(inputEvt);
                            }
                        }
                    }
                }
            }
        }

        // private methods
        void InputManager::__keyCallbackPrivate(GLFWwindow* window, int key, int scancode, int action, int mods) {
            getInstance()._keyCallback(window, key, scancode, action, mods);
        }

        void InputManager::__characterCallbackPrivate(GLFWwindow* window, unsigned int codepoint) {
            getInstance()._characterCallback(window, codepoint);
        }

        void InputManager::__scanCallbackPrivate() {
            getInstance()._scanCallback();
        }
    #endif
} /* id */
