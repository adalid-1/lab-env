
#pragma once
#include "core/app.h"
#include "Vector4D.h"
#include "ShaderObject.h";
/*
Lighting
1. Add a new node class represeting a point light source. It needs to contain position, color and
intensity.
2. Implement a Blinn-Phong shader that will show the effect of the light on the shaded object. It has
to implement diffuse lighting and specular reflectivity. The light source class has to apply its values
to the phong shader in order to update the properties.

*/

class LightNode {

public:
	Vector4D color;
	Vector4D position;
	float intensity = 1.0f;

	void setColor(GLuint r, GLuint g, GLuint b);
	void setIntensity(float newIntensity);

	void sendValuesToUniform(ShaderObject& shader);
};