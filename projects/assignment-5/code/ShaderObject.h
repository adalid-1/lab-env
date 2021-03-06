#pragma once
#include "core/app.h"
#include <string>
#include <fstream>
#include "TextureResource.h"
#include "Matrix4D.h"
#include "Vector4D.h"


class ShaderObject {
public:
	//Paths for loading from file
	const char* vsPath = "resources/shaders/VertexShader.cpp";
	const char* fsPath = "resources/shaders/FragmentShader.cpp";
	void setVsPath(const char* path);
	void setFsPath(const char* path);

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

	 ShaderObject();
	 ~ShaderObject();

	 void setup();
	 void CompileShaders();

	//Load shader from file into a string
	void LoadFromFile(const char* filename, std::string& out);
	//Call before drawing
	void UseProgram();
	//detaches shaders from program and deletes shaders and program
	void cleanup();
	//Modifying shader types
	void ModMat4fv(const std::string& name,  Matrix4D& value);
	void ModVec4f(const std::string& name, const Vector4D& value);
	void ModVec3f(const std::string& name,  Vector4D& value);

	/*
	I should do this sometime:
	 Add functions for the other types as well. It is a good idea to use a map or hashtable for storing the uniform locations once instead of performing
	a lookup every time.
	*/
};

