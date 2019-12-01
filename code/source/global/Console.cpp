#include "global/Console.hpp"

#include <stdio.h>

namespace ta {
    void Console::log(const std::string& message, ta::Console::Color color) {
        log(message, "", color);
    }

    void Console::log(const std::string& message, const std::string& file, ta::Console::Color color) {
        printf("%s%s %s\n", _colorStrings[color].c_str(), file != "" ? std::string("[" + file + "]").c_str() : "", std::string(message + _colorStrings[Console::Reset]).c_str());
    }

    void Console::success(const std::string& message, const std::string& file) {
        log(message, file, Console::Green);
    }

    void Console::warn(const std::string& message, const std::string& file) {
        log(message, file, Console::Yellow);
    }

    void Console::error(const std::string& message, const std::string& file, bool critical) {
        log((critical ? "[CRITICAL] " : "") + message, file, Console::Red);
    }

    std::string Console::color(ta::Console::Color color) {
        return _colorStrings[color];
    }
} /* ta */
