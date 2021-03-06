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
#include "ObjLoader.h"
#include "LightNode.h"

#define STRING_BUFFER_SIZE 8192

using namespace Display;
namespace Example
{
ImGuiExampleApp::ImGuiExampleApp() 
{}

ImGuiExampleApp::~ImGuiExampleApp()
{}

bool ImGuiExampleApp::Open()
{
	App::Open();
	this->window = new Display::Window;
	window->SetKeyPressFunction([this](int32, int32, int32, int32)
	{
		this->window->Close();
	});

    if (this->window->Open())
	{
		// set clear color to whatever color you want
		glClearColor(0.f, 0.f, 0.f, 0.0f);

		//Making resources
		Gnode.pointerSetup();
		//Setting up mesh, texture and shader resources
		Gnode.setup();
		Gnode.transform = Gnode.transform.translate(Vector4D(0, 0, -50, 1)) * Gnode.transform;

		Light.position.setXYZW(0.0f, 0.0f, 10.f, 1);
		Light.color.setXYZW(1.0f, 1.0f, 1.0f, 1);

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
	float angle = 0.1;
	Gnode.ShaderO->UseProgram();

	//Cam
	Camera myCam;

	//Chunky input stuff
	while (this->window->IsOpen())
	{
		window->SetMousePressFunction([this, &angle, &myCam](int key, int bulle, int action)
			{
				
				if (bulle == 1 || bulle == 2)
				{
					std::cout << key << " " << action << bulle <<  std::endl;
					switch (key)
					{
					case 0://1
						Gnode.transform = Gnode.transform * Gnode.transform.RotationY(angle);
						break;
					case 1://1
						Gnode.transform = Gnode.transform * Gnode.transform.RotationX(angle);															
						break;
					}
				}
			});
		window->SetKeyPressFunction([this,  &angle, &myCam](int key, int, int action, int mod)
		{
			if (action == 1 || action == 2)
			{
				cout << key << endl;
				switch (key)
				{
				case 49://1
					
					break;		
				case 50://2
					myCam.moveUp();
					break;
				case 51://3
					myCam.moveDown();
					break;
				case 81://q
					myCam.moveDown();
					break;
				case 87://w
					myCam.moveForward();
					break;
				case 69://e
					myCam.moveUp();
					break;
				case 82://-
					Light.position.setZ(Light.position.getZ() + 0.5);
					//Gnode.transform = Gnode.transform.translate(Vector4D(0, 0, -0.5f, 1)) * Gnode.transform;
					break;
				case 65://a
					myCam.moveLeft();
					break;
				case 83://s
					myCam.moveBack();
					break;
				case 68://d
					myCam.moveRight();
					break;
				case 70://f
					//Gnode.transform = Gnode.transform.translate(Vector4D(0, 0, 0.50, 1)) * Gnode.transform;
					Light.position.setZ(Light.position.getZ() - 0.5);
					break;
				case 263://left
					//Gnode.transform =/* Gnode.transform **/ Gnode.transform.translate(Vector4D(-0.5, 0, 0, 1)) * Gnode.transform;
					Light.position.setX(Light.position.getX() - 0.5);
					break;
				case 265://up
					//Gnode.transform = /*Gnode.transform **/ Gnode.transform.translate(Vector4D(0, 0.5, 0, 1)) * Gnode.transform;
					Light.position.setY(Light.position.getY() + 0.5);
					break;
				case 262://right
					//Gnode.transform = /*Gnode.transform **/ Gnode.transform.translate(Vector4D(0.5, 0, 0, 1)) * Gnode.transform;
					Light.position.setX(Light.position.getX() + 0.5);
					break;
				case 264://down
					//Gnode.transform = Gnode.transform.translate(Vector4D(0, -0.5, 0, 1)) * Gnode.transform;
					Light.position.setY(Light.position.getY() - 0.5);
					break;
				case 256:
					this->window->Close();
					return;
				}
			}
		});

		//Depthcheck stuff
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT);

		//Don´t know
		this->window->Update();
	
		//Light.position.setXYZW(myCam.view.get(3), myCam.view.get(7), myCam.view.get(11),1.0);

		//Sending stuff to shader
		Gnode.ShaderO->ModMat4fv("view", myCam.view);
		Gnode.ShaderO->ModMat4fv("projection", myCam.projection.transpose());
		Gnode.ShaderO->ModVec3f("lightPos0", Light.position);
		Gnode.ShaderO->ModVec3f("light_color", Light.color);
		Gnode.ShaderO->ModVec3f("cam_pos", Vector4D(myCam.view.get(3), myCam.view.get(7), myCam.view.get(11), 1.0));
		//draw
		Gnode.draw();
		//Node2.draw();
		
		// transfer new frame to window
		this->window->SwapBuffers();
	}
}
//------------------------------------------------------------------------------
void ImGuiExampleApp::RenderUI()
{
	if (this->window->IsOpen())
	{
		bool show = true;
		// create a new window
		ImGui::Begin("Shader Sources", &show, ImGuiWindowFlags_NoSavedSettings);

		// create text editors for shader code
		ImGui::InputTextMultiline("Vertex Shader", Gnode.ShaderO->vsBuffer, STRING_BUFFER_SIZE, ImVec2(-1.0f, ImGui::GetTextLineHeight() * 16),
			ImGuiInputTextFlags_AllowTabInput);
		
		ImGui::InputTextMultiline("Pixel Shader", Gnode.ShaderO->fsBuffer, STRING_BUFFER_SIZE, ImVec2(-1.0f, ImGui::GetTextLineHeight() * 16),
			ImGuiInputTextFlags_AllowTabInput);

		// apply button
		if (ImGui::Button("Apply"))
		{
			// if pressed we compile the shaders
			Gnode.ShaderO->CompileShaders();
		}
		if (Gnode.ShaderO->compilerLog.length())
		{
			// if compilation produced any output we display it here
			ImGui::TextWrapped(Gnode.ShaderO->compilerLog.c_str());
		}
		// close window
		ImGui::End();
	}
}
} // namespace Example