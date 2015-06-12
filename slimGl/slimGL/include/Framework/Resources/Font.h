#pragma once

/********************************************************************************************** 
* 										includes
**********************************************************************************************/
#include <ft2build.h>
#include FT_FREETYPE_H
#include <Framework/Drawable/TextureAtlas.h>

/********************************************************************************************** 
* 										class declaration
**********************************************************************************************/

/*!
* 	\brief	a class to wrap font files
*/
class Font
{
public:
	/*!
	* 	\brief	initialize the static member
	*/
	static void initialize();

	/*!
	* 	\brief	copies are not allowed!
	*/
	Font(const Font &font) = delete;

	/*!
	* 	\brief	assignments aren't allowed!
	*/
	Font &operator=(const Font &font) = delete;

	/*!
	* 	\brief constructor
	*/
	Font();

	/*!
	* 	\brief				loading a font file
	* 	\param filePath		the path to the ttf file
	* 	\param fontsize		the size of the font
	* 	\param face_index	the index for the face to load
	* 	\return				true if loading was succesful
	*/
	bool load(std::string filePath, unsigned int fontsize, unsigned int faceIndex = 0);

	/*!
	* 	/overload bool loadFromFace(const FT_Face &face, unsigned int fontsize);
	*/
	bool load(const FT_Face &face, unsigned int fontsize);

	/*!
	* 	\brief			get the texture atlas
	* 	\return			the texture atlas containing the chars
	*/
	TextureAtlas &getTextureAtlas();
	/*!
	* 	\brief		get the size of the character
	* 	\param c	the character you want the size from
	* 	\return		the size of c in pixels
	*/
	glm::uvec2 &getCharSize(unsigned char c);
	/*!
	* 	\brief		get the size of the string
	* 	\param c	the character you want the size from
	* 	\return		the size of c in pixels
	*/
	glm::uvec2 getStringSize(std::string s);
	/*!
	* 	\brief		get the vertical advance of the character
	* 	\param c	the character you want the size from
	* 	\return		the size of c in pixels
	*/
	unsigned int getCharAdvance(unsigned char c);
private:

	//! number of points for 1 pixel
	const static int POINTS_PER_PIXEL = 64;
	//! number of chars in each column
	const static unsigned int CHAR_PER_COLUMN = 16;
	//! number of chars in each row
	const static unsigned int CHAR_PER_ROW = 16;
	//! number of chars in each row
	const static unsigned int NUMBER_CHARS = CHAR_PER_COLUMN*  CHAR_PER_ROW;

	//! the freetype library
	static FT_Library library;
	//! a texture atlas to draw the single chars
	TextureAtlas m_textureAtlas;
	//! a texture representing the table of chars
	std::shared_ptr<Texture> m_texture;
	//! the sizes for the chars
	glm::uvec2 m_size[NUMBER_CHARS];
	//! the vertical advance for the chars
	unsigned int m_advance[NUMBER_CHARS];
};
