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

}

void GraphicsNode::setup()
{
	//load obj 
	//meshR->setupModel("resources/obj/TestOBJ.obj");
	meshR->setupCylinderModel();
	//Sets up vao, index och vertexbuffer
	meshR->SetupVertexArrayObject();
	//Setting up texture
	texR->setup();
	//loads shaders and compiles them
	ShaderO->setup();
	ShaderO->UseProgram();
	//Transform, position of this node
	Matrix4D transform;


}

void GraphicsNode::setup(const char* modelPath, const char* texturePath)
{
	//load obj 
	meshR->setupModel(modelPath);
	//Sets up vao, index och vertexbuffer
	meshR->SetupVertexArrayObject();
	//Setting up texture
	texR->setPath(texturePath);
	texR->setup();
	//loads shaders and compiles them
	ShaderO->setup();
	ShaderO->UseProgram();
	//Transform, position of this node
	Matrix4D transform;


}

void GraphicsNode::setupAndGenerateTree(std::vector<Segment> segmentList)
{
	//load obj 

	meshR->genTreeModel(segmentList);
	//Sets up vao, index och vertexbuffer
	meshR->SetupVertexArrayObject();
	//Setting up texture
	texR->setup();
	//loads shaders and compiles them
	ShaderO->setup();
	ShaderO->UseProgram();
	//Transform, position of this node
	Matrix4D transform;


}

void GraphicsNode::draw()
{
	//send transform to shader
	ShaderO->ModMat4fv("transform", transform);
	//Texture
	texR->activate();
	//Drawing the mesh
	meshR->DrawMesh();
	//Move to shaderobject?
	ShaderO->UseProgram();
	

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


//shares all smartpointers between nodes
void GraphicsNode::getPtrsFromOtherNode(GraphicsNode& otherNode)
{
	setMeshR(otherNode.getMeshR());
	setTextureR(otherNode.getTextureR());
	setShaderO(otherNode.getShaderO());
	
}
