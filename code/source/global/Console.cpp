#include "global/Console.hpp"

#include <stdio.h>

namespace id {
    void Console::log(const std::string& message, id::Console::Color color) {
        log(message, "", color);
    }

    void Console::log(const std::string& message, const std::string& file, id::Console::Color color) {
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

    std::string Console::color(id::Console::Color color) {
        return _colorStrings[color];
    }
} /* id */
