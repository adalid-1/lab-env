#pragma once
//------------------------------------------------------------------------------
/**
	Application class used for example application.
	
	(C) 2015-2018 Individual contributors, see AUTHORS file
*/
//------------------------------------------------------------------------------
#include "core/app.h"
#include "render/window.h"

#include "GraphicsNode.h"
#include "LightNode.h"

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



	GraphicsNode Gnode;
	LightNode Light;
private:

	/// show some ui things
	void RenderUI();
	// show some nanovg stuff
	void RenderNano(NVGcontext* vg);


	GLuint triangle;
	Display::Window* window;
};
} // namespace Example