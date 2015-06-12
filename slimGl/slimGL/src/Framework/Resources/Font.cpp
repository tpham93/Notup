/********************************************************************************************** 
* 										include
**********************************************************************************************/
#include <algorithm>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <Framework/Resources/Font.h>

/********************************************************************************************** 
* 										class definition
**********************************************************************************************/

FT_Library Font::library;

void Font::initialize()
{

#ifndef __FREEGLUT_H__
	FT_Error error = FT_Init_FreeType( &library);
	if (error)
	{
		std::cerr << "FreeType error: " << error << std::endl;
	}
#endif

}

Font::Font()
	:m_textureAtlas(),
	m_texture(std::make_shared<Texture>())
{

}

bool Font::load(std::string filePath, unsigned int fontsize, unsigned int faceIndex)
{
	// saving errors
	FT_Error error = 0;

#ifdef __FREEGLUT_H__
	error = FT_Init_FreeType( &library);
	if (error)
	{
		std::cerr << "FreeType error: " << error << std::endl;
		return false;
	}
#endif

	// creating a face
	FT_Face face = nullptr;

	error = FT_New_Face(library, filePath.c_str(), faceIndex, &face);
	if (!error)
	{
		load(face, fontsize);
	}
	else
	{
		std::cerr << "Error: " << error << "couldn't load the file: " << filePath << std::endl;
		return false;
	}

	FT_Done_Face(face);
	return true;
}

bool Font::load(const FT_Face &face, unsigned int fontsize)
{
	// saving errors
	FT_Error error = 0;
	// the pixels for the bitmap
	GLuint* pixels;
	// the metrics for the chars
	FT_Glyph_Metrics glyphMetrics[NUMBER_CHARS];
	// all pixels for the glyphs
	unsigned char*  glyphPixels[NUMBER_CHARS];
	// size of the created bitmap cell
	glm::ivec2 bitmapCellSize(0, 0);
	// size of the created bitmap cell
	glm::ivec2 bitmapSize(0, 0);
	// the maximal width of a char
	long maxWidth = 0;
	// the maximal bearing of a char
	long maxBearingY = 0;
	// the maximal hang of a char
	long maxHang = 0;

	// set the maximum height
	FT_Set_Pixel_Sizes(face, 0, fontsize);

	// load all glyphs
	for (int i = 0; i < NUMBER_CHARS; ++i)
	{
		// loading the i-th glyph
		error = FT_Load_Char(face, i, FT_LOAD_RENDER);
		if (error)
		{
			std::cerr << "FreeType error: " << error << std::endl;
		}

		// save the metrics
		glyphMetrics[i] = face->glyph->metrics;
		// save the bitmap size
		m_size[i] = glm::uvec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
		m_advance[i] = glyphMetrics[i].horiAdvance / POINTS_PER_PIXEL;

		glm::uvec2 &currentSize = m_size[i];
		// copy the pixels
		glyphPixels[i] = new unsigned char[currentSize.x*  currentSize.y];

		for (unsigned int y = 0; y < currentSize.y; ++y)
		{
			for (unsigned int x = 0; x < currentSize.x; ++x)
			{
				unsigned int currentIndex = x + y*  currentSize.x;
				glyphPixels[i][currentIndex] = face->glyph->bitmap.buffer[currentIndex];
			}
		}
		maxWidth = std::max(maxWidth, glyphMetrics[i].width / POINTS_PER_PIXEL);
		maxBearingY = std::max(maxBearingY, glyphMetrics[i].horiBearingY / POINTS_PER_PIXEL);
		maxHang = std::max(maxWidth, (glyphMetrics[i].horiBearingY - glyphMetrics[i].height) / POINTS_PER_PIXEL);
	}

	// calculate the size of a singl cell in th bitmap
	bitmapCellSize = glm::uvec2(maxWidth, maxBearingY + maxHang);
	// calculate the size of a singl cell in th bitmap
	bitmapSize = glm::uvec2(CHAR_PER_COLUMN*  bitmapCellSize.x, CHAR_PER_ROW*  bitmapCellSize.y);
	// create the pixels for the bitmap
	pixels = new GLuint[bitmapSize.x*  bitmapSize.y]{};

	// initialize the texture atlas
	m_textureAtlas.initialize();

	for (unsigned int charY = 0; charY < CHAR_PER_ROW; ++charY)
	{
		for (unsigned int charX = 0; charX < CHAR_PER_COLUMN; ++charX)
		{
			// currently used char
			unsigned int currentChar = charX + charY*  CHAR_PER_COLUMN;

			// calculate the start position
			glm::uvec2 startPosition(charX*  bitmapCellSize.x, charY*  bitmapCellSize.y);
			glm::uvec2 blitStartPosition(startPosition);
			blitStartPosition.y += maxBearingY - (glyphMetrics[currentChar].horiBearingY / POINTS_PER_PIXEL);

			// iterate through all pixels
			for (unsigned int glyphPixelY = 0; glyphPixelY < m_size[currentChar].y; ++glyphPixelY)
			{
				for (unsigned int glyphPixelX = 0; glyphPixelX < m_size[currentChar].x; ++glyphPixelX)
				{
					unsigned int glyphPixelIndex = glyphPixelX + glyphPixelY*   m_size[currentChar].x;

					// get the index of the pixel to set
					unsigned int bitmapX = blitStartPosition.x + glyphPixelX;
					unsigned int bitmapY = blitStartPosition.y + glyphPixelY;
					unsigned int bitmapIndex = bitmapX + bitmapY*  bitmapSize.x;
					// access the pixel as char[4] to get all 4 components
					unsigned char* components = reinterpret_cast<unsigned char* >( &pixels[bitmapIndex]);
					// r
					components[0] = 0xff;// glyphPixels[currentChar][glyphPixelIndex];
					// g
					components[1] = 0xff;// glyphPixels[currentChar][glyphPixelIndex];
					// b
					components[2] = 0xff;// glyphPixels[currentChar][glyphPixelIndex];
					// a
					components[3] = glyphPixels[currentChar][glyphPixelIndex];
				}
			}

			// add the source
			m_textureAtlas.addSource(Rect(static_cast<float>(startPosition.x), static_cast<float>(startPosition.y), static_cast<float>(bitmapCellSize.x), static_cast<float>(bitmapCellSize.y)));
		}
	}
	// load the pixel
	m_texture->loadTextureFromPixels(pixels, bitmapSize.x, bitmapSize.y);
	// initialize the texture atlas
	m_textureAtlas.initialize();
	// set the texture of the atlas
	m_textureAtlas.setTexture(m_texture);

	return true;
}

TextureAtlas &Font::getTextureAtlas()
{
	return m_textureAtlas;
}

glm::uvec2 &Font::getCharSize(unsigned char c)
{
	return m_size[c];
}

glm::uvec2 Font::getStringSize(std::string s)
{
	unsigned int width = 0;
	unsigned int height = 0;
	for (unsigned int i = 0; i < s.length(); ++i)
	{
		glm::uvec2 size = getCharSize(s[i]);
		width += getCharAdvance(s[i]);
		height = std::max(height, size.y);
	}
	return glm::uvec2(width, height);
}

unsigned int Font::getCharAdvance(unsigned char c)
{
	return m_advance[c];
}