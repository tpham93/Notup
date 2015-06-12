/********************************************************************************************** 
* 										include
**********************************************************************************************/
#include <Framework/Drawable/Text.h>

/********************************************************************************************** 
* 										class definition
**********************************************************************************************/

Text::Text()
	:m_position(),
	m_text()
{

}

void Text::initialize()
{

}

Font &Text::getFont()
{
	return*m_font;
}

void Text::setFont(std::shared_ptr<Font> font)
{
	m_font = font;
}

std::string &Text::getText()
{
	return m_text;
}

const std::string &Text::getText() const
{
	return m_text;
}

void Text::setText(std::string &text)
{
	m_text = text;
}

glm::vec2 &Text::getDestination()
{
	return m_position;
}

void Text::setDestination(glm::vec2 position)
{
	m_position = position;
}

void Text::setShaderProgram(std::shared_ptr<ShaderProgram> shaderProgram)
{
	m_shaderProgram = shaderProgram;
}

void Text::draw()
{
	// get the texture atlas of the font
	TextureAtlas &textureAtlas = m_font->getTextureAtlas();
	// set the shaderprogram for the texture atlas of the font
	textureAtlas.setShaderProgram(m_shaderProgram);
	// get the length of the text
	unsigned int textLength = static_cast<unsigned int>(m_text.size());
	// set the start position
	glm::vec2 currentPosition = m_position;

	for (unsigned int i = 0; i < textLength; ++i)
	{
		// get the current char
		unsigned char currentChar = m_text[i];
		// the index of the char
		unsigned int currentIndex = static_cast<unsigned int>(currentChar);
		// set the new source
		textureAtlas.setSource(currentIndex);
		// set the new dstination
		textureAtlas.setDestination(Rect(currentPosition.x, currentPosition.y, textureAtlas.getSource(currentIndex).getWidth(), textureAtlas.getSource(currentIndex).getHeight()));
		// draw the character
		textureAtlas.draw();
		// move the cursor
		currentPosition.x += m_font->getCharAdvance(currentChar);
	}
}