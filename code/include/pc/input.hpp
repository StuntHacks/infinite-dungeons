#ifdef __PC__
/**
 * @file pc/input.hpp
 * @brief Defines the Input class
 */
#pragma once

namespace id {
    class Application;
    class Renderer;

    /**
     * @brief Contains everything specific to PC-builds
     */
    namespace pc {
        /**
         * @brief Represents different keys
         */
        enum class Key: int {
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
            KeyPad0 = 320,    ///< 0 on keypad
            KeyPad1,          ///< 1 on keypad
            KeyPad2,          ///< 2 on keypad
            KeyPad3,          ///< 3 on keypad
            KeyPad4,          ///< 4 on keypad
            KeyPad5,          ///< 5 on keypad
            KeyPad6,          ///< 6 on keypad
            KeyPad7,          ///< 7 on keypad
            KeyPad8,          ///< 8 on keypad
            KeyPad9,          ///< 9 on keypad
            KeyPadDecimal,    ///< Decimal-point (.) on keypad
            KeyPadDivide,     ///< Divide (:) on keypad
            KeyPadMultiply,   ///< Multiply (*) on keypad
            KeyPadSubstract,  ///< Substract (-) on keypad
            KeyPadAdd,        ///< Add (+) on keypad
            KeyPadEnter,      ///< Enter on keypad
            KeyPadEqual,      ///< Equal (=) on keypad
            LeftShift = 340,  ///< Left Shift-key
            LeftControl,      ///< Left Ctrl-key
            LeftAlt,          ///< Left Alt-key
            LeftSuper,        ///< Left Super (Windows) key
            RightShift,       ///< Right Shift-key
            RightControl,     ///< Right Ctrl-key
            RightAlt,         ///< Right Alt-key
            RightSuper,       ///< Right Super (Windows) key
            Menu,             ///< Menu key
            Last = Menu,      ///< ID of last element in this enum
        };

        /**
         * @brief Represents different controller buttons (Nintendo-layout)
         */
        enum class Button: int {
            Unknown = -2,     ///< Unknown button
            None,             ///< No button (never really gets triggered, meant for internal logic)
            B,                ///< B/Circle
            A,                ///< A/Cross
            Y,                ///< Y/Triangle
            X,                ///< X/Square
            LeftBumper,       ///< Left bumper
            RightBumper,      ///< Right bumper
            Select,           ///< Select/Back
            Start,            ///< Start
            Home,             ///< Home/Guide
            LeftTrigger,      ///< Left trigger
            RightTrigger,     ///< Right trigger
            Up,               ///< D-Pad up
            Right,            ///< D-Pad right
            Down,             ///< D-Pad down
            Left,             ///< D-Pad left
            Last = Left,      ///< ID of last element in this enum
        };

        /**
         * @brief Represents the two joysticks (when using a single Joy-Con, only Joystick::Left will be in use)
         */
        enum class Joystick: int {
            Left = 0,  ///< Left
            Right = 2 ///< Right
        };

        /**
         * @brief Represents the different players
         */
        enum class Player: int {
            P1 = 0,   // Player 1
            P2,       // Player 2
            P3,       // Player 3
            P4,       // Player 4
            All       // All players
        };

        /**
         * @brief Handles user input
         */
        class Input {
        friend class id::Application;
        protected:
            static void scanInput();
        };
    } /* pc */
} /* id */
#endif
