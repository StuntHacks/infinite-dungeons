#version 430 core
layout (location = 0) in vec3 iPos;
layout (location = 1) in vec4 iColor;
layout (location = 2) in vec2 iTexCoords;
layout (location = 3) in vec3 iNormals;
out vec2 texCoords;

uniform mat4 projection;
uniform mat4 transform;

void main()
{
    gl_Position = projection * transform * vec4(iPos.xyz, 1.0);
    texCoords = iTexCoords;
}
