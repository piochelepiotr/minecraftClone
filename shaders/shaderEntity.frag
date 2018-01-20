#version 400 core

out vec4 out_Color;
in vec2 pass_textureCoords;
uniform sampler2D textureSampler;
uniform vec3 lightColour;
in vec3 surfaceNormal;
in float visibility;
uniform float shineDamper;
uniform float shineReflectivity;
uniform vec3 skyColour;
in vec3 colour;

void main()
{
    vec3 unitNormal = normalize(surfaceNormal);
    float l = 0.8;
    if(dot(unitNormal, vec3(0,1,0)) > 0.8)
    {
        l = 1;
    }
    else if(dot(unitNormal, vec3(0,-1,0)) > 0.8)
    {
        l = 0.2;
    }

    out_Color = l* texture(textureSampler, pass_textureCoords);
    out_Color = mix(vec4(skyColour, 1.0), out_Color, visibility);
    //out_Color = vec4(colour, 1.0);
}
