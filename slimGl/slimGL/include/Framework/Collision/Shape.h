#pragma once

/**********************************************************************************************
* 											include
**********************************************************************************************/
#include <Framework/Collision/ShapeType.h>
#include <Framework/Collision/CollisionInfo.h>

/**********************************************************************************************
* 										class declaration
**********************************************************************************************/
/*
*	\brief a class to abstract shapes used for collision detection
*/
class Shape
{
public:

	/*
	*	\brief			constructor
	*	\param radius	the radius for the whole shape
	*/
	Shape(float radius, glm::vec2 position);

	/*
	*	\brief	differ between different types of shapes
	*/
	virtual ShapeType getShapeType() const = 0;

	/*
	*	\brief			calculating the collision information between two shapes
	*	\param shape	the other shape, which should be tested for collision
	*	\return			information between the shapes
	*/
	virtual CollisionInfo collide(Shape& shape) = 0;

	/*
	*	\brief	the getter for the approximated radius of the shape
	*	\return	the approximated radius of the shape
	*/
	float getRadius() const;

	/*
	*	\brief	the getter for the position of the shape
	*	\return	the position of the shape
	*/
	glm::vec2 getPosition() const;

	/*
	*	\brief	the getter for the rotation of the shape
	*	\return	the rotation of the shape
	*/
	float getRotation() const;

	/*
	*	\brief			rotating the shape around the origin (0/0)
	*	\param rotation	the rotation in rad
	*/
	virtual void rotate(float rotation);

	/*
	*	\brief			tranlating the shape
	*	\param movement	the vector, in which the shape should be translated
	*/
	virtual void translate(glm::vec2 movement);

	/*
	*	\brief			setter for the rotation
	*	\param rotation	the rotation in rad
	*/
	virtual void setRotation(float rotation);

	/*
	*	\brief			setter for the position
	*	\param movement	the position of the shape
	*/
	virtual void setPosition(glm::vec2 position);
protected:
	//! the position of the shape
	glm::vec2 m_position;
	//! the rotation of the shape in rad
	float m_rotation;
	//! the approximated radius of the shape
	float m_radius;
};