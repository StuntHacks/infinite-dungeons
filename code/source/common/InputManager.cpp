#include "common/InputManager.hpp"
#include "common/Application.hpp"
#include "common/events/InputEvent.hpp"
#include "common/events/KeyPressEvent.hpp"
#include "common/events/TextEvent.hpp"

namespace id {
    void InputManager::bindInput(const std::string& id, id::InputManager::Key key) {
        m_keyBindings[id] = key;

        if (m_keys.count(key) != 0) {
            std::vector<std::string>::iterator it = std::find(m_keys[key].begin(), m_keys[key].end(), id);
            if (it != m_keys[key].end()) {
                m_keys[key].erase(it);
            }
        }

        m_keys[key].push_back(id);
    }

    bool InputManager::unbindInput(const std::string& id) {
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
            if (m_keys.count(static_cast<id::InputManager::Key>(key)) != 0) {
                for (auto& input: m_keys[static_cast<id::InputManager::Key>(key)]) {
                    id::events::InputEvent inputEvt(input, static_cast<id::events::PressEvent::State>(action));
                    id::events::KeyPressEvent keyEvt(key, static_cast<id::events::PressEvent::State>(action));

                    dispatch(inputEvt);
                    dispatch(keyEvt);
                }
            }
        }

        void InputManager::_characterCallback(GLFWwindow* window, unsigned int codepoint) {
            id::events::TextEvent evt(static_cast<wchar_t>(codepoint));
            dispatch(evt);
        }

        // private methods
        void InputManager::__keyCallbackPrivate(GLFWwindow* window, int key, int scancode, int action, int mods) {
            getInstance()._keyCallback(window, key, scancode, action, mods);
        }

        void InputManager::__characterCallbackPrivate(GLFWwindow* window, unsigned int codepoint) {
            getInstance()._characterCallback(window, codepoint);
        }
    #endif
} /* id */
