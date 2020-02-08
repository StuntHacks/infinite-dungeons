#version 430 core

const vec2 lightBias = vec2(0.7, 0.6);

in vec2 pTexCoords;
in vec3 pNormals;

out vec4 oColor;

uniform sampler2D diffuseMap;
uniform vec3 lightDirection;

void main() {
    vec4 diffuseColor = texture(diffuseMap, pTexCoords);
    vec3 unitNormal = normalize(pNormals);
    float diffuseLight = max(dot(-lightDirection, unitNormal), 0.0) * lightBias.x + lightBias.y;
    oColor = diffuseColor * diffuseLight;
}
