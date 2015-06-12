#pragma once

/**********************************************************************************************
* 											include
**********************************************************************************************/
#include <vector>
#include <Framework/Collision/Shape.h>
#include <Framework/Collision/Range.h>


/**********************************************************************************************
* 										forward declaration
**********************************************************************************************/
class CircleShape;

/**********************************************************************************************
* 										class declaration
**********************************************************************************************/
class ConvexPolygonShape : public Shape
{
public:

	/*
	*	\brief			constructor
	*	\param radius	the radius of this shape
	*	\param position	the position of this shape
	*	\param vertices	the corners of the shape
	*/
	ConvexPolygonShape(glm::vec2 position, std::vector<glm::vec2> &vertices);

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
	*	\brief			calculating the collision information between a circle and a convex polygon
	*	\param shape	the other circle shape, which should be tested for collision
	*	\return			information between the shapes
	*/
	CollisionInfo collide(CircleShape& shape);

	/*
	*	\brief			calculating the collision information between two convex polygon shapes
	*	\param shape	the other convex polygon shape, which should be tested for collision
	*	\return			information between the shapes
	*/
	CollisionInfo collide(ConvexPolygonShape& shape);

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

	/*
	*	\brief			project all vertices against an edge
	*	\param edge		the edge which should be used for projection
	*	\return			the range of the projection
	*/
	Range project(const glm::vec2 &edge);

	//! the corners of the polygon, where (0,0) is the origin at the position (0/0) and unrotated
	std::vector<glm::vec2> m_originalVertices;
	//! the edges of the polygon unrotated
	std::vector<glm::vec2> m_originalEdges;
	//! the corners of the polygon, where (0,0) is the origin at the position (0/0) and unrotated
	std::vector<glm::vec2> m_rotatedVertices;
	//! the corners of the polygon, where (0,0) is the origin
	std::vector<glm::vec2> m_vertices;
	//! the edges of the polygon
	std::vector<glm::vec2> m_edges;
};