#version 430
in vec2 ATexCoord;

out vec4 Color;
uniform sampler2D ourTexture;

uniform vec3 lightPos0;
void main()
{
    Color = texture(ourTexture, ATexCoord);
}