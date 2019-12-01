#pragma once

#include <string>

namespace ta {
    class Console {
    public:
        enum Color {
            Reset = 0,
            Black,
            Red,
            Green,
            Yellow,
            Blue,
            Magenta,
            Cyan,
            White
        };

        static void log(const std::string& message, ta::Console::Color color = ta::Console::Reset);
        static void log(const std::string& message, const std::string& file = "", ta::Console::Color color = ta::Console::Reset);
        static void success(const std::string& message, const std::string& file = "");
        static void warn(const std::string& message, const std::string& file = "");
        static void error(const std::string& message, const std::string& file = "", bool critical = false);

        static std::string color(ta::Console::Color color);
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
} /* ta */
