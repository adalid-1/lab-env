//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2018 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "exampleapp.h"
#include <cstring>
#include "imgui.h"
#include "MeshResource.h"
#include "Matrix4D.h"
#include "Vector4D.h"
#include "TextureResource.h"
#include "Camera.h"

#define STRING_BUFFER_SIZE 8192

const GLchar* vs =
"#version 430\n"
"layout(location=0) in vec3 pos;\n"
"layout(location=1) in vec2 aTexCoord;"
"out vec2 ATexCoord;\n"
"uniform mat4 transform;\n"
"uniform mat4 view;\n"
"uniform mat4 projection; \n"
"void main()\n"
"{\n"
"    gl_Position = projection * view * transform * vec4(pos, 1);\n"
"    ATexCoord = aTexCoord;\n"
"}\n";

const GLchar* ps =
"#version 430\n"
"in vec2 ATexCoord;\n"

"out vec4 Color;\n"
"uniform sampler2D ourTexture;"
"void main()\n"
"{\n"
"    Color = texture(ourTexture, ATexCoord);\n"
"}\n";
using namespace Display;
namespace Example
{
ImGuiExampleApp::ImGuiExampleApp() : vertexShader(0), pixelShader(0), program(0)
{}
ImGuiExampleApp::~ImGuiExampleApp()
{}
bool
ImGuiExampleApp::Open()
{
	App::Open();
	this->window = new Display::Window;
	window->SetKeyPressFunction([this](int32, int32, int32, int32)
	{
		this->window->Close();
	});

    if (this->window->Open())
	{
		// set clear color to red gray
		glClearColor(0.f, 0.1f, 0.1f, 0.0f);

		// create buffer for shader strings
		this->vsBuffer = new GLchar[STRING_BUFFER_SIZE];
		this->fsBuffer = new GLchar[STRING_BUFFER_SIZE];

		// copy the hardcoded shader into buffer
		strncpy(this->vsBuffer, vs, STRING_BUFFER_SIZE);
		strncpy(this->fsBuffer, ps, STRING_BUFFER_SIZE);

		// compile the shaders in the buffers
		this->CompileShaders();


		// set ui rendering function
		this->window->SetUiRender([this]()
		{
			this->RenderUI();
		});

		return true;
	}
	return false;
}
//------------------------------------------------------------------------------
void
ImGuiExampleApp::Run()
{
	float angle = 1.0;

	MeshResource* meshList = new MeshResource;

	MeshResource mesh;
	mesh.generateCube(0.1f);
	mesh.SetupVertexArrayObject();
	
	//Setting up texture
	TextureResource myTexture;
	myTexture.setup();
	
	//Transform
	Matrix4D transform;
	Matrix4D mat2;

	//Cam
	Camera myCam;

	while (this->window->IsOpen())
	{
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT);
		this->window->Update();

		glUseProgram(this->program);

		//Texture
		myTexture.activate();

		//rotation around cube at a given radius
		myCam.lookat(1.0);

		//sending stuff to shaders
		unsigned int transformLoc = glGetUniformLocation(this->program, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_TRUE, &transform[0]);
		unsigned int viewLoc = glGetUniformLocation(this->program, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_TRUE, &myCam.view[0]);
		unsigned int projLoc = glGetUniformLocation(this->program, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, &myCam.projection[0]);

		mesh.DrawMesh();
		angle = angle + 0.005;
		
		// transfer new frame to window
		this->window->SwapBuffers();
	}
}

//------------------------------------------------------------------------------
/**
*/
void
ImGuiExampleApp::RenderUI()
{
	if (this->window->IsOpen())
	{
		bool show = true;
		// create a new window
		ImGui::Begin("Shader Sources", &show, ImGuiWindowFlags_NoSavedSettings);

		// create text editors for shader code
		ImGui::InputTextMultiline("Vertex Shader", vsBuffer, STRING_BUFFER_SIZE, ImVec2(-1.0f, ImGui::GetTextLineHeight() * 16),
			ImGuiInputTextFlags_AllowTabInput);
		
		ImGui::InputTextMultiline("Pixel Shader", fsBuffer, STRING_BUFFER_SIZE, ImVec2(-1.0f, ImGui::GetTextLineHeight() * 16),
			ImGuiInputTextFlags_AllowTabInput);

		// apply button
		if (ImGui::Button("Apply"))
		{
			// if pressed we compile the shaders
			this->CompileShaders();
			
		}
		if (this->compilerLog.length())
		{
			// if compilation produced any output we display it here
			ImGui::TextWrapped(this->compilerLog.c_str());
		}
		// close window
		ImGui::End();
	}
}

//------------------------------------------------------------------------------
/**
*/
void
ImGuiExampleApp::CompileShaders()
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

//------------------------------------------------------------------------------
/**
*/


} // namespace Example