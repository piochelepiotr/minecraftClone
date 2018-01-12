#version 400 core

out vec4 out_Color;
in vec2 pass_textureCoords;
uniform sampler2D textureSampler;

void main()
{
    out_Color = texture(textureSampler, pass_textureCoords);
}