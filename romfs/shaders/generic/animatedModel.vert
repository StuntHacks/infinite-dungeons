#version 430 core

layout (location = 0) in vec3 iPos;
layout (location = 1) in vec2 iTexCoords;
layout (location = 2) in vec3 iNormals;
layout (location = 3) in ivec4 iJoints;
layout (location = 4) in vec4 iWeights;

out vec2 pTexCoords;
out vec3 pNormals;

const int MaxWeights = 4;
const int MaxJoints = 50;
uniform mat4 jointTransforms[MaxJoints];
uniform mat4 projectionViewMatrix;

void main() {
    vec4 totalLocalPos = vec4(0.0);
    vec4 totalNormal = vec4(0.0);

    for (int i = 0; i < MaxWeights; i++) {
        mat4 jointTransform = jointTransforms[iJoints[i]];
        vec4 posePosition = jointTransform * vec4(iPos, 1.0);
        totalLocalPos += posePosition * iWeights[i];

        vec4 worldNormal = jointTransform * vec4(iNormals, 0.0);
        totalNormal += worldNormal * iWeights[i];
    }

    gl_Position = projectionViewMatrix * totalLocalPos;
    pTexCoords = iTexCoords;
    pNormals = totalNormal.xyz;
}
