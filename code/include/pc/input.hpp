#ifdef __PC__
/**
 * @file pc/input.hpp
 * @brief Defines the Input class
 */
#pragma once

#include "common/graphics/Vertex.hpp"

namespace id {
    class Application;

    /**
     * @brief Contains everything specific to PC-builds
     */
    namespace pc {
        /**
         * @brief Represents the different buttons
         */
        enum Button {
            Unknown = -1,     ///< Unknown key
            None,             ///< No key (never really gets triggered, meant for internal logic)
            Space = 32,       ///< Space-key
            Apostrophe = 39,  ///< Apostrophe-key (')
            Comma = 44,       ///< Comma-key
            Minus,            ///< Minus-key
            Period,           ///< Period-key
            Slash,            ///< Slash-key
            Num0,             ///< 0-key
            Num1,             ///< 1-key
            Num2,             ///< 2-key
            Num3,             ///< 3-key
            Num4,             ///< 4-key
            Num5,             ///< 5-key
            Num6,             ///< 6-key
            Num7,             ///< 7-key
            Num8,             ///< 8-key
            Num9,             ///< 9-key
            Semicolon = 59,   ///< Semicolon-key
            Equal = 61,       ///< Equal-key (=)
            A = 65,           ///< A-key
            B,                ///< B-key
            C,                ///< C-key
            D,                ///< D-key
            E,                ///< E-key
            F,                ///< F-key
            G,                ///< G-key
            H,                ///< H-key
            I,                ///< I-key
            J,                ///< J-key
            K,                ///< K-key
            L,                ///< L-key
            M,                ///< M-key
            N,                ///< N-key
            O,                ///< O-key
            P,                ///< P-key
            Q,                ///< Q-key
            R,                ///< R-key
            S,                ///< S-key
            T,                ///< T-key
            U,                ///< U-key
            V,                ///< V-key
            W,                ///< W-key
            X,                ///< X-key
            Y,                ///< Y-key
            Z,                ///< Z-key
            LeftBracket,      ///< Left bracket-key ([)
            Backslash,        ///< Backslash-key (\)
            RightBracket,     ///< Right bracket-key (])
            GraveAccent = 96, ///< Grave-accent-key (`)
            World1 = 161,     ///< Non-US-key 1
            World2,           ///< Non-US-key 2
            Escape = 256,     ///< Escape-key
            Enter,            ///< Enter-key
            Tab,              ///< Tab-key
            Backspace,        ///< Backspace
            Insert,           ///< Insert
            Delete,           ///< Delete
            Right,            ///< Right
            Left,             ///< Left
            Down,             ///< Down
            Up,               ///< Up
            PageUp,           ///< Page-up-key
            PageDown,         ///< Page-down-key
            Home,             ///< Home-key
            End,              ///< End
            CapsLock = 280,   ///< Capslock
            ScrollLock,       ///< Scroll-lock
            NumLock,          ///< Numlock
            Print,            ///< Print-key
            Pause,            ///< Pause-key
            F1 = 290,         ///< F1-key
            F2,               ///< F2-key
            F3,               ///< F3-key
            F4,               ///< F4-key
            F5,               ///< F5-key
            F6,               ///< F6-key
            F7,               ///< F7-key
            F8,               ///< F8-key
            F9,               ///< F9-key
            F10,              ///< F10-key
            F11,              ///< F11-key
            F12,              ///< F12-key
            F13,              ///< F13-key
            F14,              ///< F14-key
            F15,              ///< F15-key
            F16,              ///< F16-key
            F17,              ///< F17-key
            F18,              ///< F18-key
            F19,              ///< F19-key
            F20,              ///< F20-key
            F21,              ///< F21-key
            F22,              ///< F22-key
            F23,              ///< F23-key
            F24,              ///< F24-key
            F25,              ///< F25-key
            KeyPad0 = 320, ///< 0 on keypad
            KeyPad1, ///< 1 on keypad
            KeyPad2, ///< 2 on keypad
            KeyPad3, ///< 3 on keypad
            KeyPad4, ///< 4 on keypad
            KeyPad5, ///< 5 on keypad
            KeyPad6, ///< 6 on keypad
            KeyPad7, ///< 7 on keypad
            KeyPad8, ///< 8 on keypad
            KeyPad9, ///< 9 on keypad
            KeyPadDecimal, ///< Decimal-point (.) on keypad
            KeyPadDivide, ///< Divide (:) on keypad
            KeyPadMultiply, ///< Multiply (*) on keypad
            KeyPadSubstract, ///< Substract (-) on keypad
            KeyPadAdd, ///< Add (+) on keypad
            KeyPadEnter, ///< Enter on keypad
            KeyPadEqual, ///< Equal (=) on keypad
            LeftShift = 340, ///< Left Shift-key
            LeftControl, ///< Left Ctrl-key
            LeftAlt, ///< Left Alt-key
            LeftSuper, ///< Left Super (Windows) key
            RightShift, ///< Right Shift-key
            RightControl, ///< Right Ctrl-key
            RightAlt, ///< Right Alt-key
            RightSuper, ///< Right Super (Windows) key
            Menu,       ///< Menu key
            Last = Menu, ///< ID of last element in this enum
        };

        /**
         * @brief Handles user input
         */
        class Input {
        friend class id::Application;
        public:
            /**
             * @brief Represents the different buttons
             */
            enum Button {
                None = -1, ///< -key
            };

            enum class Joystick: int {
                // Left = JOYSTICK_LEFT,
                // Right = JOYSTICK_RIGHT
            };

            /**
             * @brief Represents the different players
             */
            enum class Player: int {
                P1 = 0,   // Player 1
                P2,       // Player 2
                P3,       // Player 3
                P4,       // Player 4
                P5,       // Player 5
                P6,       // Player 6
                P7,       // Player 7
                P8,       // Player 8
                Handheld, // Handheld
                All       // All players
            };

            /**
             * @brief Contains all the input data for the current frame
             */
            struct InputData {
                /**
                 * @brief Contains input data on a per-player basis
                 */
                struct PlayerInput {
                    /**
                     * @brief Contains all the information about this player's controller
                     */
                    struct ControllerData {
                        bool connected; ///< Whether a controller is connected on this slot
                    };

                    int pressedButtons,  ///< Buttons that have been pressed by this player this frame
                        downButtons,     ///< Buttons that are pressed by this player this frame, regardless whether they were pressed in the last frame or not
                        releasedButtons; ///< Buttons that have been released by this player this frame
                    ControllerData controllerData; ///< Controller data
                    id::graphics::Vector2i joystickCartesian[2];
                    id::graphics::Vector2f joystickPolar[2];
                };

                int pressedButtons,  ///< Buttons that have been pressed by any player this frame
                    downButtons,     ///< Buttons that are pressed by any player this frame, regardless whether they were pressed in the last frame or not
                    releasedButtons; ///< Buttons that have been released by any player this frame
                PlayerInput playerData[(int) Player::All]; ///< Input data for every player
            };

            /**
             * @brief Gets the buttons down in bits
             * @param  player The player to read the buttons from
             * @return        Button values in bits
             */
            static inline unsigned int buttonsDown(Player player = Player::All) {
                return (player == Player::All ? m_inputData.downButtons : m_inputData.playerData[(int) player].downButtons);
            }

            /**
             * @brief Gets the buttons pressed in bits
             * @param  player The player to read the buttons from
             * @return        Button values in bits
             */
            static inline unsigned int buttonsPressed(Player player = Player::All) {
                return (player == Player::All ? m_inputData.pressedButtons : m_inputData.playerData[(int) player].pressedButtons);
            }

            /**
             * @brief Gets the buttons released in bits
             * @param  player The player to read the buttons from
             * @return        Button values in bits
             */
            static inline unsigned int buttonsReleased(Player player = Player::All) {
                return (player == Player::All ? m_inputData.releasedButtons : m_inputData.playerData[(int) player].releasedButtons);
            }

            /**
             * Returns whether the given button is pressed this frame but wasn't pressed in the last frame
             * @param  buttons The button
             * @param  player  The player to read the buttons from
             * @return         Whether the button is pressed or not
             */
            static inline bool buttonPressed(Button buttons, Player player = Player::All) {
                return (buttonsPressed(player) & buttons);
            }

            /**
             * @brief Returns whether the given button is pressed this frame regardless whether it was pressed in the last frame
             * @param  buttons The button
             * @param  player  The player to read the buttons from
             * @return         Whether the button is pressed or not
             */
            static inline bool buttonDown(Button buttons, Player player = Player::All) {
                return (buttonsDown(player) & buttons);
            }

            /**
             * @brief Returns whether the given button was released (i.e. isn't pressed this frame but was in the last frame)
             * @param  buttons The button
             * @param  player  The player to read the buttons from
             * @return         Whether the button was released or not
             */
            static inline bool buttonReleased(Button buttons, Player player = Player::All) {
                return (buttonsReleased(player) & buttons);
            }

            /**
             * @brief Returns the position of the given stick in cartesian coordinates
             * @param  stick  The stick to query
             * @param  player The player to query from
             * @return        A vector consisting of the x- and y-position (both between [-32767; 32768])
             */
            static inline id::graphics::Vector2i getJoystickCartesian(id::pc::Input::Joystick stick, Player player) {
                return m_inputData.playerData[(int) player].joystickCartesian[static_cast<int>(stick)];
            }

            /**
             * @brief Returns the position of the given stick in polar coordinates
             * @param  stick  The stick to query
             * @param  player The player to query from
             * @return        A vector consisting of the angle (in degrees) and the length (between [-1.0; 1.0])
             */
            static inline id::graphics::Vector2f getJoystickPolar(id::pc::Input::Joystick stick, Player player) {
                return m_inputData.playerData[(int) player].joystickPolar[static_cast<int>(stick)];
            }

        private:
            static void scanInput();
            static InputData m_inputData;
        };
    } /* pc */
} /* id */
#endif
