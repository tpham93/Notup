#pragma once

/********************************************************************************************** 
* 										includes
**********************************************************************************************/
#include <glm/glm.hpp>

/********************************************************************************************** 
* 										class declaration
**********************************************************************************************/

/*!
* 	\brief	a basic rectangle class
*/
class Rect
{
public:
	/*!
	* 	\brief			constructor
	* 	\param x		the x coordinate of the top left corner
	* 	\param y		the y coordinate of the top left corner
	* 	\param width	the width of the rectangle
	* 	\param height	the height of the rectangle
	*/
	Rect(float x, float y, float width, float height);

	/*!
	* 	\brief				constructor
	* 	\param topLeft		the corner of the rectangle on the top left
	* 	\param bottomRight	the corner of the rectangle on the bottom right
	*/
	Rect(glm::vec2 topLeft, glm::vec2 bottomRight);

	/*!
	* 	\brief			check for intersection between 2 rectangles
	* 	\param rect		the other rectangle to test for intersection
	* 	\return			true if both rectangle intersect
	*/
	bool intersects(const Rect &rect);

	/*!
	* 	\brief		get the x value of the top left corner
	* 	\return		x value of the top left corner
	*/
	float getX() const;

	/*!
	* 	\brief		set the x value of the top left corner
	* 	\param x	the new x of the rectangle
	*/
	void setX(float x);

	/*!
	* 	\brief		get the y value of the top left corner
	* 	\return		y value of the top left corner
	*/
	float getY() const;

	/*!
	* 	\brief		set the y value of the top left corner
	* 	\param y	the new y of the rectangle
	*/
	void setY(float y);

	/*!
	* 	\brief		get the width of the rectangle
	* 	\return		the width of the rectangle
	*/
	float getWidth() const;

	/*!
	* 	\brief			set the width of the rectangle
	* 	\param width	the new width of the rectangle
	*/
	void setWidth(float width);

	/*!
	* 	\brief		get the height of the rectangle
	* 	\return		the height of the rectangle
	*/
	float getHeight() const;

	/*!
	* 	\brief			set the height of the rectangle
	* 	\param height	the new height of the rectangle
	*/
	void setHeight(float height);

	/*!
	* 	\brief		get the center of the rectangle
	* 	\return		the center of the rectangle
	*/
	glm::vec2 getCenter() const;

protected:
	//! the top left corner of the rectangle
	float m_x;

	//! the top left corner of the rectangle
	float m_y;

	//! the width of the rectangle
float m_width;

	//! the height of the rectangle
float m_height;
};
