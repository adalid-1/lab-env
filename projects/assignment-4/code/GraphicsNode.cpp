#include "GraphicsNode.h"

GraphicsNode::GraphicsNode()
{

	transform = Matrix4D();

}

void GraphicsNode::pointerSetup()
{
	meshR = std::make_shared<MeshResource>();
	texR = std::make_shared<TextureResource>();
	ShaderO = std::make_shared<ShaderObject>();
	O_Loader = std::make_shared<ObjLoader>();
}

void GraphicsNode::setup()
{
	//setting up mesh and generating a cube
	meshR->generateCube(0.1f);
	
	
	//load obj instead
	//meshR->setupModel(*O_Loader);
	
	meshR->Setup();

	//Setting up texture
	texR->setup();

	//
	ShaderO->setup();
	ShaderO->UseProgram();
	//Transform
	Matrix4D transform;


}

void GraphicsNode::draw()
{

	ShaderO->ModMat4fv("transform", transform);
	//Texture
	texR->activate();
	//Drawing the mesh
	meshR->DrawMesh();
	//Move to shaderobject?
	ShaderO->UseProgram();
	//cam going around cube, radius as param

}

std::shared_ptr<MeshResource> GraphicsNode::getMeshR()
{
	return meshR;
}

std::shared_ptr<TextureResource> GraphicsNode::getTextureR()
{
	return texR;
}

std::shared_ptr<ShaderObject> GraphicsNode::getShaderO()
{
	return ShaderO;
}

std::shared_ptr<ObjLoader> GraphicsNode::getObjLoader()
{
	return O_Loader;
}

void GraphicsNode::setMeshR(std::shared_ptr<MeshResource> meshRptr)
{
	meshR = meshRptr;

}

void GraphicsNode::setTextureR(std::shared_ptr<TextureResource> textureRptr)
{
	texR = textureRptr;
}

void GraphicsNode::setShaderO(std::shared_ptr<ShaderObject> shaderOptr)
{
	ShaderO = shaderOptr;
}

void GraphicsNode::setObjLoader(std::shared_ptr<ObjLoader> objptr)
{
	O_Loader = objptr;
}
//shares all smartpointers between nodes
void GraphicsNode::getPtrsFromOtherNode(GraphicsNode& otherNode)
{
	setMeshR(otherNode.getMeshR());
	setTextureR(otherNode.getTextureR());
	setShaderO(otherNode.getShaderO());
	setObjLoader(otherNode.getObjLoader());
}
