#pragma once

/**********************************************************************************************
* 											include
**********************************************************************************************/
#include <Framework/Collision/Shape.h>


/**********************************************************************************************
* 										class declaration
**********************************************************************************************/
class CircleShape : public Shape
{
public:

	/*
	*	\brief			constructor
	*	\param radius	the radius of this shape
	*	\param position	the position of this shape
	*/
	CircleShape(float radius, glm::vec2 position);

	/*
	*	\brief	differ between different types of shapes
	*/
	virtual ShapeType getShapeType() const;

	/*
	*	\brief			calculating the collision information between two shapes
	*	\param shape	the other shape, which should be tested for collision
	*	\return			information between the shapes
	*/
	virtual CollisionInfo collide(Shape& shape);

	/*
	*	\brief			calculating the collision information between two circle shapes
	*	\param shape	the other circle shape, which should be tested for collision
	*	\return			information between the shapes
	*/
	CollisionInfo collide(CircleShape& shape);
};