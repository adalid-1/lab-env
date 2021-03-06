#version 430
layout(location=0) in vec3 pos;
layout(location=1) in vec2 aTexCoord;
layout(location =2) in vec3 vertex_normal;
out vec3 vs_pos;
out vec2 ATexCoord;
out vec3 vs_normal;
out vec3 FragPos;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;
void main()
{
	    gl_Position = projection * view * transform * vec4(pos, 1);
		FragPos = vec3(transform * vec4(pos, 1));
	    ATexCoord = aTexCoord;
		vs_normal = mat3(transform) * vertex_normal;
}