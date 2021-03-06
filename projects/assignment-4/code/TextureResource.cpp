#include "TextureResource.h"
//#include <iostream>

TextureResource::TextureResource()
{
	//std::cout << "made texR" << std::endl;
}

TextureResource::~TextureResource()
{
	
	if (texture)
	{
		glDeleteTextures(1, &texture);
	}
}

void TextureResource::setup()
{
		//Binding texture
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//Wrap along x-axis
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//Wrap along y-axis
	
		//Filtrering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//load image
		LoadFromFile("resources/textures/wall.jpg");
		
		
		//Uppload to GPU
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		
		//Clean up data that we don?t need anymore
		stbi_image_free(data);
	
}

void TextureResource::activate()
{
	glBindTexture(GL_TEXTURE_2D, texture);

}

void TextureResource::LoadFromFile(const char* fileName) {

	data = stbi_load(fileName, &width, &height, &nrChannels, 4);
}