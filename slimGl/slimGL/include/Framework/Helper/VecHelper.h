#pragma once
#include <glm/glm.hpp>

class VecHelper
{
public:
	/*!
	*	\brief		calculatnig on which side the point p is in relation to the edge going from a to b
	*	\param a	the first point of the edge
	*	\param b	the second point of the edge
	*	\param p	the point you want to know the side from
	*	\return		0 if p is on the edge, positive is p is left, otherwise negative
	*/
	static float sideOfPoint(glm::vec2 a, glm::vec2 b, glm::vec2 p);
};