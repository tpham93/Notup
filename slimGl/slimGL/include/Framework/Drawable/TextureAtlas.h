#pragma once

/********************************************************************************************** 
* 										includes
**********************************************************************************************/
#include <vector>
#include <Framework/Drawable/Sprite.h>

/********************************************************************************************** 
* 										class declaration
**********************************************************************************************/

/*!
* 	\brief	a class to wrap up a texture with multiple images
*/
class TextureAtlas : public Sprite
{
public:
	/*!
	* 	\brief constructor
	*/
	TextureAtlas();

	/*!
	* 	\brief			constructor
	* 	\param texture	the texture you want to draw
	*/
	TextureAtlas(std::shared_ptr<const Texture> texture);

	/*!
	* 	\brief				set the source
	* 	\param rect			the new rectangle
	* 	\return				index with which you can st the source
	* 	\pre				none
	* 	\post				the added rectangle can be used by s
	*/
	size_t addSource(const Rect &rect);

	/*!
	* 	\brief				set the source
	* 	\param i			the index of the saved source
	*/
	void setSource(unsigned int i);

	/*!
	* 	\brief				get the i-th source
	* 	\param i			the index of the saved source
	*/
	const Rect &getSource(unsigned int i) const;
private:
	//! the part of the texture which should be drawn
	std::vector<Rect> m_availableSources;
};
