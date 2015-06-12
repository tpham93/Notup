/********************************************************************************************** 
* 										include
**********************************************************************************************/
#include <GL/glew.h>
#include <IL/il.h>
#include <IL/ilu.h>
#include<assert.h>
#include<algorithm>
#include <Framework/Resources/Texture.h>
#include <Framework/Helper/Helper.h>
/********************************************************************************************** 
* 										static member declaration
**********************************************************************************************/
GLuint Texture::maxNumberTextures = 0;
std::vector<GLuint> Texture::currentBoundTexture = std::vector<GLuint>();

/********************************************************************************************** 
* 										class definition
**********************************************************************************************/

void Texture::initialize()
{
	GLint  textureNumber = 0;
	// get the number of maximal bound textures
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &textureNumber);
	maxNumberTextures = static_cast<GLuint>(textureNumber);
	// initialize the vector to keep track of the bound textures
	currentBoundTexture.resize(maxNumberTextures, 0);
}

GLuint Texture::getMaxNumberTextures()
{
	return maxNumberTextures;
}

std::vector<GLuint> Texture::getCurrentBoundTextures()
{
	return currentBoundTexture;
}

GLuint Texture::getCurrentBoundTexture(GLuint textureUnit)
{
	return currentBoundTexture[textureUnit];
}

Texture::Texture()
	: m_textureId(0),
	m_width(0),
	m_height(0)
{

}

Texture::~Texture()
{
	// deleting texture if there is any
	if (m_textureId != 0)
	{
		// make the texture unbound
		std::replace(currentBoundTexture.begin(), currentBoundTexture.end(), m_textureId, static_cast<GLuint>(0));
		// freeing the texture if there is one
		freeTexture();
	}
}  

bool Texture::loadTextureFromPixels(GLuint* pixels, GLuint imgWidth, GLuint imgHeight, GLint internalFormat, GLint format)
{
	// check if the pointer of the pixels is not a null pointer
	assert(pixels != nullptr  &&"pixels must not be a null pointer!");
	// check if the sizes are bigger than 0
	assert(imgWidth != 0  &&"the width must be greater than 0!");
	assert(imgHeight != 0  &&"the height must be greater than 0!");

	// set the new sizes
	m_width = imgWidth;
	m_height = imgHeight;

	//// deleting previous texture if there is any
	//if (m_textureId != 0)
	//{
	//	// freeing the texture if there is already one
	//	freeTexture();
	//	m_textureId = 0;
	//}

	if (m_textureId == 0)
	{
		// generating a texture on the gpu
		glGenTextures(1, &m_textureId);
	}

	// binding the correct texture
	bind();
	// uploading the pixels to the gpu
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	return Helper::checkGlForError(std::cerr, "pixels couldn't be loaded");
}


bool Texture::loadTextureFromFile(std::string filepath)
{
	// the id of the image loaded 
	ILuint imgId = 0;
	// creating an image
	imgId = ilGenImage();
	// bind the created image
	ilBindImage(imgId);

	// loading the file
	ILboolean succesfulLoading = ilLoadImage(filepath.c_str());
	// bool to determine the correct return value
	bool textureLoaded = false;
	// check if loading the texture was succesful
	if (succesfulLoading)
	{
		ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
		// get the size of the images
		GLuint imageWidth = static_cast<GLuint>(ilGetInteger(IL_IMAGE_WIDTH));
		GLuint imageHeight = static_cast<GLuint>(ilGetInteger(IL_IMAGE_HEIGHT));

		// load the texture by getting the data as pixels
		textureLoaded = loadTextureFromPixels(reinterpret_cast<GLuint* >(ilGetData()), imageWidth, imageHeight);

		if (!textureLoaded)
		{
			// check for occured errors
			Helper::checkIlForError(std::cerr, " couldn't create texture from image!");
		}
	}
	else
	{
		// check for occured errors
		Helper::checkIlForError(std::cerr, filepath + " couldn't be loaded!");
	}

	// deleting the created image
	ilDeleteImage(imgId);

	// return true if the file could be loaded and if a texture could be generated from the file
	return succesfulLoading && textureLoaded;
}


void Texture::freeTexture()
{
	// check if there is a texture to delete
	assert(m_textureId != 0  &&"there should be a texture to destroy!");

	// delete the texture
	glDeleteTextures(1, &m_textureId);

	// reset all parameter
	m_textureId = 0;
	m_width = 0;
	m_height = 0;
}

void Texture::bind(GLuint textureUnit) const
{
	// check if the number of texture units is not too high
	if (maxNumberTextures >= textureUnit)
	{
		if (currentBoundTexture[textureUnit] != m_textureId)
		{
			// set the active texture to the given texture unit
			glActiveTexture(GL_TEXTURE0 + textureUnit);
			// binding the texture
			glBindTexture(GL_TEXTURE_2D, m_textureId);

			currentBoundTexture[textureUnit] = m_textureId;
		}
	}
	else
	{
		// the texture unit is too high
		std::cerr << "the texture unit is too high!" << std::endl;
	}
}


void Texture::manage(GLuint textureId, GLuint width, GLuint height)
{
	// deleting texture if there is any
	if (m_textureId != 0)
	{
		// make the texture unbound
		std::replace(currentBoundTexture.begin(), currentBoundTexture.end(), m_textureId, static_cast<GLuint>(0));
		// freeing the texture if there is one
		freeTexture();
	}

	m_textureId = textureId;
	m_width = width;
	m_height = height;
}
GLuint Texture::getTextureID() const
{
	return m_textureId;
}

GLuint Texture::getWidth() const
{
	return m_width;
}

GLuint Texture::getHeight() const
{
	return m_height;
}
