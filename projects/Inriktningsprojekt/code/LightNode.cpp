#include "LightNode.h"

void LightNode::setColor(GLuint r, GLuint g, GLuint b)
{
	color.setXYZW(r, g, b, 0);
}

void LightNode::setIntensity(float newIntensity)
{
	intensity = newIntensity;
}

void LightNode::sendValuesToUniform(ShaderObject& shader)
{
	color = color * intensity;
	shader.ModVec3f("lightPos0", position);
	shader.ModVec3f("light_color", color);
}
