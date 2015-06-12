#pragma once

/********************************************************************************************** 
* 										includes
**********************************************************************************************/
#include <string>
#include <vector>
#include <GL/glew.h>

/********************************************************************************************** 
* 										class declaration
**********************************************************************************************/

/*!
* 	\brief	a simple class wrapping up opengl textures
*/
class Texture
{
public:
	/*!
	* 	\brief	initialize the static member
	*/
	static void initialize();

	/*!
	* 	\brief		initialize the static member
	* 	\return		the id of the bound texture
	* 	\pre		called initialize
	* 	\post		none
	*/
	static GLuint getMaxNumberTextures();

	/*!
	* 	\brief	get the bound textures for each texture unit
	* 	\return	the id of the bound texture
	* 	\pre	called initialize
	* 	\post	none
	*/
	static std::vector<GLuint> getCurrentBoundTextures();

	/*!
	* 	\brief				get the id of the bound texture for the given texture unit
	* 	\param textureUnit	the texture unit you want the bound texture from
	* 	\return				the id of the bound texture
	* 	\pre				called initialize
	* 	\post				none
	*/
	static GLuint getCurrentBoundTexture(GLuint textureUnit = 0);

	/*!
	* 	\brief	copies are not allowed!
	*/
	Texture(const Texture &texture) = delete;

	/*!
	* 	\brief	assignments aren't allowed!
	*/
	Texture &operator=(const Texture &texture) = delete;

	/*!
	* 	\brief				standard constructor
	* 	\pre				none
	* 	\post				none
	* 	\sideeffect			none
	*/
	Texture();

	/*!
	* 	\brief				destructor
	* 	\pre				none
	* 	\post				texture gets deleted from the gpu if there is any
	* 	\sideeffect			if the texture is bound anywhere the default texture gets bound (0)
	*/
	virtual ~Texture();

	/*!
	* 	\brief					loading a texture from an array of GLuint
	* 	\param pixels			the array to define the color of the pixel
	* 	\param imgWidth			the width of the image
	* 	\param imgHeight		the height of the image
	* 	\param internalFormat	the format of the texture
	* 	\return					true if the loading was successful
	* 	\pre					none
	* 	\post					pixels gets uploaded to the gpu and can be used
	* 	\sideeffect				if another texture is already loaded it gets deleted
	* 							texture is on the gpu and bound to texture unit 0
	*/
	bool loadTextureFromPixels(GLuint* pixels, GLuint imgWidth, GLuint imgHeight, GLint internalFormat = GL_RGBA, GLint format = GL_RGBA);


	/*!
	* 	\brief				loading a texture from a file
	* 	\param filepath		the filepath to the image
	* 	\return				true if the loading was successful
	* 	\pre				\sa loadTextureFromPixels
	* 	\post				\sa loadTextureFromPixels
	* 	\sideeffect			\sa loadTextureFromPixels
	*/
	bool loadTextureFromFile(std::string filepath);

	/*!
	* 	\brief				deleting the texture from the gpu
	* 	\return				void
	* 	\pre				texture is loaded
	* 	\post				texture gets deleted from the gpu
	* 	\sideeffect			if the texture is bound anywhere the default texture gets bound (0)
	*/
	void freeTexture();

	/*!
	* 	\brief				binding the texture to a specific texture unit (default = 0)
	* 	\param textureUnit	the texture unit the texture should be bound to
	* 	\return				void
	* 	\pre				none
	* 	\post				pixels gets uploaded to the gpu and can be used
	* 	\sideeffect			texture is bound on the given textureUnit
	*/
	void bind(GLuint textureUnit = 0) const;

	/*!
	* 	\brief				managing an already loaded texture
	* 	\param textureId	the id of the texture which should be bound
	* 	\param width		the width of the bound texture
	* 	\param height		the height of the bound texture
	*/
	void manage(GLuint textureId, GLuint width, GLuint height);

	/*!
	* 	\brief		gets the texture id
	* 	\return		the texture id
	*/
	GLuint getTextureID() const;

	/*!
	* 	\brief				gets the width of the texture
	* 	\return				the width of the texture
	*/
	GLuint getWidth() const;

	/*!
	* 	\brief				gets the height of the texture
	* 	\return				the height of the texture
	*/
	GLuint getHeight() const;

private:
	//! the current bound texture
	static GLuint maxNumberTextures;
	//! the current bound texture
	static std::vector<GLuint> currentBoundTexture;
	//! the id of the texture in the gpu
	GLuint m_textureId;
	//! the width of the texture
	GLuint m_width;
	//! the height of the texture
	GLuint m_height;
};
