#version 400 core

out vec4 out_Color;
in vec2 pass_textureCoords;
uniform sampler2D textureSampler;
uniform vec3 lightColour;
in vec3 surfaceNormal;
in vec3 toLightVector;
in vec3 toCameraVector;
in float visibility;
uniform float shineDamper;
uniform float shineReflectivity;
uniform vec3 skyColour;
in vec3 colour;

void main()
{
    vec3 unitNormal = normalize(surfaceNormal);
    vec3 unitLight = normalize(toLightVector);

    //diffuse
    float nDot1 = dot(unitNormal, unitLight);
    float brightness = max(nDot1, 0.2);
    vec3 diffuse = brightness * lightColour;

    //specular
    vec3 unitCamera = normalize(toCameraVector);
    vec3 lightDirection = - unitLight;
    vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);

    float specularFactor = max(dot(reflectedLightDirection, unitCamera), 0.0);
    float damperFactor = pow(specularFactor, shineDamper);
    vec3 finalSpecular = damperFactor * shineReflectivity * lightColour;

    out_Color = (vec4(diffuse, 1.0)* texture(textureSampler, pass_textureCoords)) + vec4(finalSpecular, 1.0);
    out_Color = mix(vec4(skyColour, 1.0), out_Color, visibility);
    //out_Color = vec4(colour, 1.0);
}
