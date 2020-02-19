#include "common/loaders/Loader.hpp"

namespace id {
    namespace loaders {
        bool Loader::loadFromFile(const std::string& filepath) {
            std::ifstream file(filepath);
            std::string buffer((std::istreambuf_iterator<char>(file)),
                                std::istreambuf_iterator<char>());

            return loadFromMemory(buffer);
        }
    } /* loaders */
} /* id */
