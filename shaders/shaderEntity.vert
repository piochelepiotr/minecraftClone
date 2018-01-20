#version 400 core

in vec3 position;
in vec2 textureCoords;
in vec3 normal;
out vec2 pass_textureCoords;
out vec3 surfaceNormal;
out float visibility;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform vec3 lightPosition;

uniform float numberOfRows;
uniform vec2 textureOffset;

const float density = 0.00;
const float gradient = 1.5;
out vec3 colour;

void main()
{
    vec4 worldPosition = (transformationMatrix * vec4(position, 1.0));
    vec4 posRelativeToCamera = viewMatrix * worldPosition;
    gl_Position = projectionMatrix * posRelativeToCamera;
    //pass_textureCoords = (textureCoords / numberOfRows) + textureOffset;
    pass_textureCoords = textureCoords;
    surfaceNormal = (transformationMatrix * vec4(normal, 0.0)).xyz;

    float distance = length(posRelativeToCamera.xyz);
    visibility = exp(-pow((distance*density), gradient));
    visibility = clamp(visibility, 0, 1);
}
