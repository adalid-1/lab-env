#pragma once
#include "core/app.h"
#include <string>
#include <fstream>
#include "TextureResource.h"
#include "Matrix4D.h"
#include "Vector4D.h"


class ShaderObject {
public: 

	//Handles
	GLuint program;
	GLuint vertexShader;
	GLuint pixelShader;

	GLchar* vsBuffer;
	GLchar* fsBuffer;
	std::string compilerLog;

	//Stores shader data read from file
	std::string vertShaderStr;
	std::string fragShaderStr;

	 const GLchar* vs; 
	 const GLchar* ps; 

	 ShaderObject();
	 void setup();
	 void CompileShaders();

	//Load shader from file into a string
	void LoadFromFile(const char* filename, std::string& out);
	//Call before drawing
	void UseProgram();

	//Modifying shader types
	void ModMat4fv(const std::string& name,  Matrix4D& value);
	void ModVec4f(const std::string& name, const Vector4D& value);


};

