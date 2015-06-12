#pragma once

/********************************************************************************************** 
* 										includes
**********************************************************************************************/
#include <memory>
#include <Framework/Drawable/Drawable.h>
#include <Framework/Resources/Font.h>

/********************************************************************************************** 
* 										class declaration
**********************************************************************************************/

/*!
* 	\brief	a class to wrap text drawn by fonts
*/
class Text : public Drawable
{
public:
	/*!
	* 	\brief constructor
	*/
	Text();

	/*!
	* 	\brief initializing buffer
	*/
	virtual void initialize() override;

	/*!
	* 	\brief		get the font
	* 	\return		the font used by the text, nullptr if there is none
	*/
	Font &getFont();

	/*!
	* 	\brief			set the font
	* 	\param font		the font which should be used
	*/
	void setFont(std::shared_ptr<Font> font);

	/*!
	* 	\brief		get the text
	* 	\return		the text which should be drawn
	*/
	std::string &getText();

	/*!
	* 	/overload const Font &getText() const
	*/
	const std::string &getText() const;

	/*!
	* 	\brief			set the text
	* 	\param text		the text which should be drawn
	*/
	void setText(std::string &text);

	/*!
	* 	\brief		get the destination
	* 	\return		the position drawn text
	*/
	glm::vec2 &getDestination();

	/*!
	* 	\brief			set the destination the current width and height stays the same
	* 	\param position	the position where the texture should be drawn
	*/
	void setDestination(glm::vec2 position);

	/*!
	* 	\brief			set the scale of the text
	* 	\param position	the position where the texture should be drawn
	*/
	glm::vec2 getSize();

	/*!
	* 	\brief					set the shader which should be used to draw
	* 	\param shaderProgram	the shaderprgram you want to use for drawing
	* 	\pre					none
	* 	\post					shader will be used for the following draw calls
	*/
	virtual void setShaderProgram(std::shared_ptr<ShaderProgram> shaderProgram) override;

	/*!
	* 	\brief			drawing the text to the destination
	*/
	virtual void draw();
private:

	// the startposition of the text
	glm::vec2 m_position;
	// the text which shold be drawn
	std::string m_text;
	// the font which should be used
	std::shared_ptr<Font> m_font;

};
