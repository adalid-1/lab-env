#pragma once
//------------------------------------------------------------------------------
/**
	Application class used for example application.
	
	(C) 2015-2018 Individual contributors, see AUTHORS file
*/
//------------------------------------------------------------------------------
#include "core/app.h"
#include "render/window.h"
#include "ShaderObject.h"
#include "GraphicsNode.h"
#include "Camera.h"

namespace Example
{
class ImGuiExampleApp : public Core::App
{
public:
	/// constructor
	ImGuiExampleApp();
	/// destructor
	~ImGuiExampleApp();

	/// open app
	bool Open();
	/// run app
	void Run();

	//
	ShaderObject MyShaders;
	
	GraphicsNode Gnode;
private:

	/// show some ui things
	void RenderUI();

	GLuint triangle;
	Display::Window* window;
};
} // namespace Example