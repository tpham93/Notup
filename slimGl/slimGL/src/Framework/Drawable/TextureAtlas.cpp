/********************************************************************************************** 
* 										include
**********************************************************************************************/
#include <Framework/Drawable/TextureAtlas.h>

/********************************************************************************************** 
* 										class definition
**********************************************************************************************/

TextureAtlas::TextureAtlas()
	:TextureAtlas(nullptr)
{

}

TextureAtlas::TextureAtlas(std::shared_ptr<const Texture> texture)
	: Sprite(texture),
	m_availableSources()
{

}

size_t TextureAtlas::addSource(const Rect &rect)
{
	// add the source rectangle
	m_availableSources.push_back(rect);
	// return the index of the addd rectangle
	return m_availableSources.size() - 1;
}

void TextureAtlas::setSource(unsigned int i)
{
	// set the new source
	Sprite::setSource(m_availableSources[i]);
}

const Rect &TextureAtlas::getSource(unsigned int i) const
{
	// set the new source
	return m_availableSources[i];
}