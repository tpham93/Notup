#pragma once

/**********************************************************************************************
* 										includes
**********************************************************************************************/
#include <glm/glm.hpp>
#include <Framework/Helper/Rect.h>

/**********************************************************************************************
* 										class declaration
**********************************************************************************************/

/*!
* 	\brief	a basic box class
*/
class Box : public Rect
{
public:
	/*!
	* 	\brief			constructor
	* 	\param x		the x coordinate of the rear top left corner
	* 	\param y		the y coordinate of the rear top left corner
	* 	\param z		the z coordinate of the rear top left corner
	* 	\param width	the width of the box
	* 	\param height	the height of the box
	* 	\param depth	the depth of the box
	*/
	Box(float x, float y, float z, float width, float height, float depth);

	/*!
	* 	\brief				constructor
	* 	\param topLeft		the corner of the box on the rear top left
	* 	\param bottomRight	the corner of the box on the front bottom right
	*/
	Box(glm::vec3 rearTopLeft, glm::vec3 frontBottomRight);

	/*!
	* 	\brief			check for intersection between 2 boxs
	* 	\param rect		the other box to test for intersection
	* 	\return			true if both box intersect
	*/
	bool intersects(const Box &box);

	/*!
	* 	\brief		get the z value of the rear top left corner
	* 	\return		z value of the rear top left corner
	*/
	float getZ() const;

	/*!
	* 	\brief		set the z value of the rear top left corner
	* 	\param z	the new z of the box
	*/
	void setZ(float z);

	/*!
	* 	\brief		get the width of the box
	* 	\return		the width of the box
	*/
	float getDepth() const;

	/*!
	* 	\brief			set the depth of the box
	* 	\param width	the new depth of the box
	*/
	void setDepth(float depth);

	/*!
	* 	\brief		get the center of the box
	* 	\return		the center of the box
	*/
	glm::vec3 getCenter() const;

	/*!
	*	\brief	get the rear bottom left corner of the box
	*	\return the coordinates of the rear top left corner
	*/
	glm::vec3 getRearBottomLeft() const;

	/*!
	*	\brief	get the front top right corner of the box
	*	\return the coordinates of the rear top left corner
	*/
	glm::vec3 getFrontTopRight() const;
private:
	//! the top left corner of the box
	float m_z;

	//! the height of the box
	float m_depth;
};
