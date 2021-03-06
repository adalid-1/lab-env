#include "TextureResource.h"

TextureResource::TextureResource()
{	
}
TextureResource::~TextureResource()
{
	cleanup();
}

void TextureResource::cleanup()
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
		LoadFromFile(path);
				
		//Uppload to GPU
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		
		//Clean up data that we don´t need anymore
		stbi_image_free(data);
	
}

void TextureResource::activate()
{
	glBindTexture(GL_TEXTURE_2D, texture);

}

void TextureResource::setPath(const char* newPath)
{
	path = newPath;
}

void TextureResource::LoadFromFile(const char* fileName) {

	data = stbi_load(fileName, &width, &height, &nrChannels, 4);
}
//Stbi stuff
// Basic usage (see HDR discussion below for HDR usage):
//    int x,y,n;
//    unsigned char *data = stbi_load(filename, &x, &y, &n, 0);
//    // ... process data if not NULL ...
//    // ... x = width, y = height, n = # 8-bit components per pixel ...
//    // ... replace '0' with '1'..'4' to force that many components per pixel
//    // ... but 'n' will always be the number that it would have been if you said 0
//    stbi_image_free(data)
//
// Standard parameters:
//    int *x                 -- outputs image width in pixels
//    int *y                 -- outputs image height in pixels
//    int *channels_in_file  -- outputs # of image components in image file
//    int desired_channels   -- if non-zero, # of image components requested in result