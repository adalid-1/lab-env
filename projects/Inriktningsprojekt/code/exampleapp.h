#pragma once
//------------------------------------------------------------------------------
/**
	Application class used for example application.
	
	(C) 2015-2018 Individual contributors, see AUTHORS file
*/
//------------------------------------------------------------------------------
#include "core/app.h"
#include "render/window.h"
#include "Lsystem.h"
#include "GraphicsNode.h"
#include "LightNode.h"
#include "MeshResource.h"
#include "Matrix4D.h"
#include "Vector4D.h"
#include "TextureResource.h"
#include "Camera.h"
#include "ObjLoader.h"
//#include "LightNode.h"

#include "LsystemPart.h"
#include <vector>

class LsystemPart;
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
	std::vector<LsystemPart> lista2;
	std::vector<LsystemPart> lista;

	std::vector<GraphicsNode> nodeList;
	std::vector<GraphicsNode> LeafList;
	GraphicsNode* Gnode;
	GraphicsNode LeafNode;
	LightNode Light;
private:

	/// show some ui things
	void RenderUI();
	void setupTreeGraphicsNode();
	void rebuildModel();
	// show some nanovg stuff
	void RenderNano(NVGcontext* vg);


	Lsystem treeGenerator;
	bool drawLeaf = false;
	int nr = 1;
	float AngleStep = 0.1;
	int randomStep = 1;
	float LengthStep = 0.1;
	bool* generateProductions = new bool(false);
	bool* shadedSmooth = new bool(true);
	//bool* foo;


	GLuint triangle;
	Display::Window* window;
};
} // namespace Example