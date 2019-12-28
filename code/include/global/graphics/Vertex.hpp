#pragma once

namespace ta {
    namespace graphics {
        struct Vector2i {
            int u = 0;
            int v = 0;
        };

        struct Vector3i {
            int x = 0;
            int y = 0;
            int z = 0;
        };

        struct Vector4i {
            int x = 0;
            int y = 0;
            int z = 0;
            int w = 0;
        };

        struct Vector2f {
            float u = 0.0f;
            float v = 0.0f;
        };

        struct Vector3f {
            float x = 0.0f;
            float y = 0.0f;
            float z = 0.0f;
        };

        struct Vector4f {
            float x = 0.0f;
            float y = 0.0f;
            float z = 0.0f;
            float w = 0.0f;
        };

        struct Vertex {
            Vector3f position;
            Vector4f color;
            Vector2f texCoords;
            Vector3f normals;
        };

    } /* graphics */
} /* ta */
