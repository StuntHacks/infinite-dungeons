/**
 * @file common/InputManager.hpp
 * @brief Defines the InputManager-class, for platform-independent input-capturing
 */
#pragma once

#include <functional>
#include <map>

#include "opengl.hpp"
#include "common/EventDispatcher.hpp"
#include "common/Singleton.hpp"
#include "common/Event.hpp"
#include "common/events/PressEvent.hpp"
#include "common/graphics/Vertex.hpp"
#include "pc/pc.hpp"
#include "switch/switch.hpp"

#ifdef __SWITCH__
    #include <switch.h>
#endif

namespace id {
    namespace graphics {
        class Renderer;
    } /* graphics */

    /**
     * @brief Handles input in a platform-independent way
     *
     * In order not to have to write specific input-code for every, platform,
     * the InputManager uses "inputs" in the form of strings instead. For example,
     * instead of having to listen to the A-button, you register a callback to the "confirm"-input.
     *
     * At instantiation, the following inputs are bound:
     */
    class InputManager: public id::EventDispatcher, public id::Singleton<InputManager> {
    friend class id::Singleton<InputManager>;
    friend class id::graphics::Renderer;
    public:
        #if defined(__SWITCH__)
            using Button = id::nx::Button; ///< Defines different Buttons on the Switch
            using Joystick = id::nx::Joystick; ///< Defines different sticks on the Switch
            using Player = id::nx::Player; ///< Defines different players on the Switch
        #elif defined(__PC__)
            using Key = id::pc::Key; ///< Defines different Keys on the PC
            using Button = id::pc::Button; ///< Defines different Keys on the PC
            using Joystick = id::pc::Joystick; ///< Defines different sticks on the PC
            using Player = id::pc::Player; ///< Defines different players/controllers on the PC
        #endif

        /**
         * @brief Destructor
         */
        virtual ~InputManager() { /* do nothing */ };

        id::events::PressEvent::State getCachedInputState(const std::string& id, bool preferButtons = false);

        id::graphics::Vector2f getJoystickCartesian(Joystick stick);

        id::graphics::Vector2f getJoystickPolar(Joystick stick);

        /**
         * @brief Binds an input to the given Key. All callbacks registered to this input will get called when the given Key is pressed
         * @param id  The input to bind
         * @param key The key to bind to
         */
        void bindInput(const std::string& id, Key key);

        /**
         * @brief Binds an input to the given Button. All callbacks registered to this input will get called when the given Button is pressed
         * @param id     The input to bind
         * @param button The Button to bind to
         */
        void bindInput(const std::string& id, Button button);

        /**
         * @brief Unbinds an input from every hardware
         * @param  id The input to unbind
         * @return    Whether the unbinding was successful (usually only fails if no such input is bound)
         */
        void unbindInput(const std::string& id);

        /**
         * @brief Unbinds a key-input
         * @param  id The input to unbind
         * @return    Whether the unbinding was successful (usually only fails if no such input is bound)
         */
        bool unbindKeyInput(const std::string& id);

        /**
         * @brief Unbinds a button-input
         * @param  id The input to unbind
         * @return    Whether the unbinding was successful (usually only fails if no such input is bound)
         */
        bool unbindButtonInput(const std::string& id);

        /**
         * @brief Unbinds all inputs
         */
        void clearInputs();

        /**
         * @brief Registers a callback to the given input. The callback will get called when the given input gets triggered
         * @param  input    The input to register to
         * @param  callback The callback to register. See id::EventDispatcher::registerCallback() for more information
         * @return          The id of the newly registered callback
         */
        const std::string registerCallback(const std::string& input, std::function<void(id::Event&)> callback);

    protected:
        #if defined(__PC__)
            /**
             * @brief GLFW key-callback
             *
             * See https://www.glfw.org/docs/latest/input_guide.html for more information
             */
            void _keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

            void _characterCallback(GLFWwindow* window, unsigned int codepoint);

            void _scanCallback();
        #endif

    private:
        InputManager() { /* do nothing */ };

        #if defined(__PC__)
            static void __keyCallbackPrivate(GLFWwindow* window, int key, int scancode, int action, int mods);
            static void __characterCallbackPrivate(GLFWwindow* window, unsigned int codepoint);
            static void __scanCallbackPrivate();
        #endif

        /* data */
        std::map<std::string, Key> m_keyBindings;
        std::map<Key, std::vector<std::string>> m_keys;

        std::map<std::string, Button> m_buttonBindings;
        std::map<Button, std::vector<std::string>> m_buttons;
        std::map<Button, id::events::PressEvent::State> m_cachedButtonStates;
    };
} /* id */
