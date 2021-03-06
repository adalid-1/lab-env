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

		//Setup light
		Light.position.setXYZW(0.0f, 3.0f, 12.f, 1);
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
	
	//Cam
	Camera myCam;
	myCam.view = myCam.view * myCam.view.translate(Vector4D(0,0 , -30, 0));

	//For rotations
	float angle = 0.05;
	//variables for input 
	bool mbOnePressed = false;
	bool mbTwoPressed = false;
	//mousepositions
	float mouseX;
	float mouseY;
	//change in mousepositions
	float mouseDx;
	float mouseDy;

	while (this->window->IsOpen())
	{
		//Chunky input stuff
		//In here we check what key is pressed and sets a bool to true if pressed and to false when released
		window->SetMousePressFunction([this, &angle, &myCam, &mbOnePressed, &mbTwoPressed](int key, int action, int mod)
			{
				switch (key)
				{
				case 0://mb1 

					switch (action)
					{
					case 0://mb1 
						mbOnePressed = false;
						break;
					case 1://mb2
						mbOnePressed = true;
						break;
					}
					break;

				case 1://mb2

					switch (action)
					{
					case 0://mb1 
						mbTwoPressed = false;
						break;
					case 1://mb2
						mbTwoPressed = true;
						break;
					}
					break;
				}
			});
		//Calls movement functions based on key pressed
		window->SetKeyPressFunction([this,  &angle, &myCam](int key, int, int action, int mod)
		{
			if (action == 1 || action == 2)
			{
				cout << key << endl;
				switch (key)
				{
				case 49://1
					Light.intensity = Light.intensity + 0.01;
					break;		
				case 50://2
					Light.intensity = Light.intensity - 0.01;
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
		//In here we check how much the mouse is moving while left or right is pressed, if movement (dx and/or dy) 
		//is above a treshold we either rotate cube or cam
		window->SetMouseMoveFunction([this, angle, &myCam, &mouseX, &mouseY, &mouseDx, &mouseDy, &mbOnePressed, &mbTwoPressed](float x, float y)mutable {

			if (mbOnePressed > 0) {
				mouseDx = mouseX - x;
				mouseDy = mouseY - y;
				mouseX = x;
				mouseY = y;
				float sensitivity = 0.25;
				angle = angle * sensitivity;

				int deltaTreshold = 2;
				if (mouseDx > deltaTreshold) {
					if (mouseDy < -deltaTreshold) {
						//myCam.rotateView(angle, -angle);
					}
					else if (mouseDy > deltaTreshold)
					{
						//myCam.rotateView(angle, angle);
					}
					else {
						myCam.rotateView(angle, 0);
					}
				}
				else if (mouseDx < -deltaTreshold)
				{
					if (mouseDy < -deltaTreshold) {

						//myCam.rotateView(-angle, -angle);
					}
					else if (mouseDy > deltaTreshold)
					{
						//myCam.rotateView(-angle, angle);
					}
					else {
						myCam.rotateView(-angle, 0);
					}
				}
				else {
					if (mouseDy < -deltaTreshold) {

						myCam.rotateView(.0f, -angle);
					}
					else if (mouseDy > deltaTreshold)
					{
						myCam.rotateView(.0f, angle);
					}
				}
			}
			if (mbTwoPressed > 0) {
				mouseDx = mouseX - x;
				mouseDy = mouseY - y;
				mouseX = x;
				mouseY = y;
				int deltaTreshold = 2;
				//disabled diagonal rotation of the model because it was disgusting but it works 
				if (mouseDx > deltaTreshold) {
					if (mouseDy < -deltaTreshold) {

						//Gnode.transform = Gnode.transform.RotationY(-angle) * Gnode.transform.RotationX(angle) * Gnode.transform;

					}
					else if (mouseDy > deltaTreshold)
					{

						//Gnode.transform = Gnode.transform.RotationY(-angle) * Gnode.transform.RotationX(-angle) * Gnode.transform;
					}
					else {

						Gnode.transform = Gnode.transform.RotationY(-angle) * Gnode.transform;
					}
				}
				else if (mouseDx < -deltaTreshold)
				{
					if (mouseDy < -deltaTreshold) {
						//Gnode.transform = Gnode.transform.RotationY(angle) * Gnode.transform.RotationX(angle) * Gnode.transform;
					}
					else if (mouseDy > deltaTreshold)
					{
						//Gnode.transform = Gnode.transform.RotationY(angle) * Gnode.transform.RotationX(-angle) * Gnode.transform;
					}
					else {

						Gnode.transform = Gnode.transform.RotationY(angle) * Gnode.transform;
					}
				}
				else {
					if (mouseDy < -deltaTreshold) {
						Gnode.transform = Gnode.transform.RotationX(angle) * Gnode.transform;
					}
					else if (mouseDy > deltaTreshold)
					{
						Gnode.transform = Gnode.transform.RotationX(-angle) * Gnode.transform;
					}
				}
			}

			});
		//Depthcheck stuff
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT);

		//Don´t really know
		this->window->Update();
	
		//Sending stuff to shaders
		Gnode.ShaderO->ModMat4fv("view", myCam.view);
		Gnode.ShaderO->ModMat4fv("projection", myCam.projection.transpose());
		Gnode.ShaderO->ModVec3f("cam_pos", Vector4D(myCam.view.get(3), myCam.view.get(7), myCam.view.get(11), 1.0));
		Light.sendValuesToUniform(*Gnode.getShaderO());
		//draw
		Gnode.draw();

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
			Gnode.ShaderO->UseProgram();
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