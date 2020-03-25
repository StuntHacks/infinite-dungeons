#include "common/loaders/implementations/AssimpLoader.hpp"
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace id {
    namespace loaders {
        bool AssimpLoader::loadFromMemory(const std::string& buffer) {
            using namespace std::string_literals;

            // And have it read the given file with some example postprocessing
            // Usually - if speed is not the most important aspect for you - you'll
            // propably to request more postprocessing than we do in this example.
            const aiScene* scene = m_importer.ReadFileFromMemory(buffer.c_str(), buffer.size(),
                    aiProcess_CalcTangentSpace       |
                    aiProcess_Triangulate            |
                    aiProcess_JoinIdenticalVertices  |
                    aiProcess_SortByPType);

            // If the import failed, report it
            if (scene) {
                // We're done. Everything will be cleaned up by the importer destructor
                id::Console::success("Successfully loaded model!", "AssimpLoader.cpp:" + std::to_string(__LINE__));
                return true;
            }

            id::Console::error("Failed to load model:\n"s + m_importer.GetErrorString(), "AssimpLoader.cpp:" + std::to_string(__LINE__));
            return false;
        }
    } /* loaders */
} /* id */
