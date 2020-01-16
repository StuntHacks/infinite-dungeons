/**
 * @file common/graphics/Vertex.hpp
 * @brief Defines the Vertex- and Vector-structs
 */
#pragma once

namespace id {
    namespace graphics {
        /**
         * @brief A vector consisting of two integers
         */
        struct Vector2i {
            int u = 0; ///< The u-component
            int v = 0; ///< The v-component
        };

        /**
         * @brief A vector consisting of three integers
         */
        struct Vector3i {
            int x = 0; ///< The x-component
            int y = 0; ///< The y-component
            int z = 0; ///< The z-component
        };

        /**
         * @brief A vector consisting of four integers
         */
        struct Vector4i {
            int x = 0; ///< The x-component
            int y = 0; ///< The y-component
            int z = 0; ///< The z-component
            int w = 0; ///< The w-component
        };

        /**
         * @brief A vector consisting of two floats
         */
        struct Vector2f {
            float u = 0.0f; ///< The u-component
            float v = 0.0f; ///< The v-component
        };

        /**
         * @brief A vector consisting of three floats
         */
        struct Vector3f {
            float x = 0.0f; ///< The x-component
            float y = 0.0f; ///< The y-component
            float z = 0.0f; ///< The z-component
        };

        /**
         * @brief A vector consisting of four floats
         */
        struct Vector4f {
            float x = 0.0f; ///< The x-component
            float y = 0.0f; ///< The y-component
            float z = 0.0f; ///< The z-component
            float w = 0.0f; ///< The w-component
        };

        /**
         * @brief A simple vertex consisting of a position, a color, texture coordinates and normals
         */
        struct Vertex {
            Vector3f position;  ///< The position
            Vector4f color;     ///< The color
            Vector2f texCoords; ///< The texture coordinates
            Vector3f normals;   ///< The normals
        };

    } /* graphics */
} /* id */
