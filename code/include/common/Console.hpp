/**
 * @file common/Console.hpp
 * @brief Defines the Console-class
 */
#pragma once

#include <string>

namespace id {
    /**
     * @brief Allows for easy logging via nxlink
     */
    class Console {
    public:
        /**
         * @brief Text colors
         */
        enum Color {
            Reset = 0, ///< Reset text color
            Black,     ///< Black
            Red,       ///< Red
            Green,     ///< Green
            Yellow,    ///< Yellow
            Blue,      ///< Blue
            Magenta,   ///< Magenta
            Cyan,      ///< Cyan
            White      ///< White
        };

        /**
         * @brief Logs a message with the given color
         * @param message The message
         * @param color   The color
         */
        static void log(const std::string& message, id::Console::Color color = id::Console::Reset);

        /**
         * @brief Logs a message with the given color in the format "[file] message"
         * @param message The message
         * @param file    The file
         * @param color   The color
         */
        static void log(const std::string& message, const std::string& file = "", id::Console::Color color = id::Console::Reset);

        /**
         * @brief Logs a message in green in the format "[file] message"
         * @param message The message
         * @param file    The file
         */
        static void success(const std::string& message, const std::string& file = "");

        /**
         * @brief Logs a message in yellow in the format "[file] message"
         * @param message The message
         * @param file    The file
         */
        static void warn(const std::string& message, const std::string& file = "");

        /**
         * @brief Logs a message in red in the format "[file] message"
         * @param message The message
         * @param file    The file
         */
        static void error(const std::string& message, const std::string& file = "", bool critical = false);

        /**
         * @brief Converts a Console::Color-value to an ANSI color code
         * @param  color The color
         * @return       The corresponding color code
         */
        static std::string color(id::Console::Color color);
    private:
        static inline const std::string _colorStrings[] = {
            "\x1b[0m",
            "\x1b[30m",
            "\x1b[31;1m",
            "\x1b[32;1m",
            "\x1b[33;1m",
            "\x1b[34;1m",
            "\x1b[35;1m",
            "\x1b[36;1m",
            "\x1b[37;1m"
        };
        /* data */
    };
} /* id */
