#version 430 core
in vec2 texCoords;
out vec4 oColor;

uniform sampler2D text;
uniform float opacity;
uniform vec3 color;

void main()
{
    oColor = vec4(texture(text, texCoords).x * color.x, texture(text, texCoords).y * color.y, texture(text, texCoords).z * color.z, texture(text, texCoords).w * opacity);
}
