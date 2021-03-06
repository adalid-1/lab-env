#version 430
in vec2 ATexCoord;

out vec4 Color;
uniform sampler2D ourTexture;
void main()
{
    Color = texture(ourTexture, ATexCoord);
}