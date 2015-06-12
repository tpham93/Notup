#pragma once

/**********************************************************************************************
* 											include
**********************************************************************************************/
#include <glm/glm.hpp>

/**********************************************************************************************
* 										forward declaration
**********************************************************************************************/
class Shape;

/**********************************************************************************************
* 										class declaration
**********************************************************************************************/
/*
*	\brief	a collection of a collision check of shapes
*/
class CollisionInfo
{
public:
	/*
	*	\brief constructor for non colliding objects
	*/
	CollisionInfo(Shape& shape1, Shape& shape2);

	/*
	*	\brief constructor for colliding objects
	*/
	CollisionInfo(Shape& shape1, Shape& shape2, glm::vec2 &mtv, float distance);

	/*
	*	\brief	gets the first shape
	*	\return	the first shape
	*/
	const Shape& getShape1() const;

	/*
	*	\brief	gets the second shape
	*	\return	the second shape
	*/
	const Shape& getShape2() const;

	/*
	*	\brief	checks if the first and the scond shape are colliding
	*	\return	true, if both shapes are colliding
	*/
	bool isColliding() const;

	/*
	*	\brief	get the direction, in which th first object has to b translated to resolve the collection
	*	\return	the direction of the Mtv
	*/
	const glm::vec2& getMtv() const;

	/*
	*	\brief	get the distanceof the mtv
	*	\return	the distance of the Mtv
	*/
	float getDistance() const;
private:
	//! the first shape
	Shape &m_shape1;
	//! the second shape
	Shape &m_shape2;
	//! true, if both shapes are colliding
	bool m_collides;
	//! the direction of the minimum translation vector
	glm::vec2 m_mtv;
	//! the distance of the minimum translation vector
	float m_distance;
};