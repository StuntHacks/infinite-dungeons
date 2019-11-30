#pragma once

namespace ta {
    namespace graphics {
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
