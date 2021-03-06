
#include "ShaderObject.h"


#define STRING_BUFFER_SIZE 8192


void ShaderObject::setVsPath(const char* path)
{
	vsPath = path;
}

void ShaderObject::setFsPath(const char* path)
{
	fsPath = path;
}

//
ShaderObject::ShaderObject() : vertexShader(0), pixelShader(0), program(0)
{
}
ShaderObject::~ShaderObject()
{
	cleanup();
}
//Loads shaders from file, formating and compiles the shaders
void ShaderObject::setup()
{
	//Load shaders 
	LoadFromFile(vsPath, vertShaderStr);
	LoadFromFile(fsPath, fragShaderStr);

	// create buffer for shader strings
	this->vsBuffer = new GLchar[STRING_BUFFER_SIZE];
	this->fsBuffer = new GLchar[STRING_BUFFER_SIZE];

	// copy the loaded shader into buffer
	strncpy(this->vsBuffer, vertShaderStr.c_str(), STRING_BUFFER_SIZE);
	strncpy(this->fsBuffer, fragShaderStr.c_str(), STRING_BUFFER_SIZE);

	// compile the shaders in the buffers
	this->CompileShaders();
}

//Load a file into a given string
void ShaderObject::LoadFromFile(const char* filename, std::string& out) {

	using namespace std;
	//Temp string for loading each line
	string line;
	//Tries to open file 
	ifstream myfile(filename);

	//Read file line after line 
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			out = out + line + "\n";
		}
		myfile.close();
	}
	//If the file wasn´t availiable print error 
	else cout << "unable to open" << endl;
	return;
}

void ShaderObject::UseProgram()
{
	glUseProgram(program);
}

void ShaderObject::CompileShaders()
{

	// check if shader already exists
	if (this->program)
	{
		glDeleteProgram(this->program);
		this->program = 0;
	}
	if (this->vertexShader)
	{
		glDeleteShader(this->vertexShader);
		this->vertexShader = 0;
	}
	if (this->pixelShader)
	{
		glDeleteShader(this->pixelShader);
		this->pixelShader = 0;
	}

	this->compilerLog.clear();

	// setup vertex shader
	this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLint length = std::strlen(this->vsBuffer);
	glShaderSource(this->vertexShader, 1, &this->vsBuffer, &length);
	glCompileShader(this->vertexShader);

	// get error log
	GLint shaderLogSize;
	glGetShaderiv(this->vertexShader, GL_INFO_LOG_LENGTH, &shaderLogSize);
	if (shaderLogSize > 0)
	{
		GLchar* buf = new GLchar[shaderLogSize];
		glGetShaderInfoLog(this->vertexShader, shaderLogSize, NULL, buf);
		this->compilerLog.append(buf);
		printf("[VERTEX SHADER COMPILE ERROR]: %s", buf);
		delete[] buf;
	}

	// setup pixel shader
	this->pixelShader = glCreateShader(GL_FRAGMENT_SHADER);
	length = std::strlen(this->fsBuffer);
	glShaderSource(this->pixelShader, 1, &this->fsBuffer, &length);
	glCompileShader(this->pixelShader);

	// get error log
	shaderLogSize;
	glGetShaderiv(this->pixelShader, GL_INFO_LOG_LENGTH, &shaderLogSize);
	if (shaderLogSize > 0)
	{
		GLchar* buf = new GLchar[shaderLogSize];
		glGetShaderInfoLog(this->pixelShader, shaderLogSize, NULL, buf);
		this->compilerLog.append(buf);
		printf("[PIXEL SHADER COMPILE ERROR]: %s", buf);
		delete[] buf;
	}

	// create a program object
	this->program = glCreateProgram();
	glAttachShader(this->program, this->vertexShader);
	glAttachShader(this->program, this->pixelShader);
	glLinkProgram(this->program);
	glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &shaderLogSize);
	if (shaderLogSize > 0)
	{
		GLchar* buf = new GLchar[shaderLogSize];
		glGetProgramInfoLog(this->program, shaderLogSize, NULL, buf);
		this->compilerLog.append(buf);
		printf("[PROGRAM LINK ERROR]: %s", buf);
		delete[] buf;
	}
}

//Sends matrices to the shaders
	void ShaderObject::ModMat4fv(const std::string& name,  Matrix4D& value)
	{
		unsigned int transformLoc = glGetUniformLocation(this->program, name.c_str());
		glUniformMatrix4fv(transformLoc, 1, GL_TRUE, &value[0]);
	}

	void ShaderObject::ModVec4f(const std::string& name, const Vector4D& value)
	{
		unsigned int transformLoc = glGetUniformLocation(this->program, name.c_str());
		glUniform4f(transformLoc, value[0], value[1], value[2], value[3]);
	}

	void ShaderObject::ModVec3f(const std::string& name,  Vector4D& value)
	{
		unsigned int transformLoc = glGetUniformLocation(this->program, name.c_str());
		//glUniform3fv(transformLoc, 1, &value[0] );
		glUniform3f(transformLoc, value.getX(), value.getY(), value.getZ());
		

	}

	void ShaderObject::cleanup()
	{
		glDetachShader(program, vertexShader);
		glDetachShader(program, pixelShader);
	
		glDeleteShader(vertexShader);
		glDeleteShader(pixelShader);
		glDeleteProgram(program);

	}



