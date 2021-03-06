#version 430
layout(location=0) in vec3 pos;
layout(location=1) in vec2 aTexCoord;
out vec2 ATexCoord;
uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;
void main()
{
	    gl_Position = projection * view * transform * vec4(pos, 1);
	    ATexCoord = aTexCoord;
}