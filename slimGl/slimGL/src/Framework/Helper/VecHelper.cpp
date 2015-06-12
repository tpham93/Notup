#include <Framework/Helper/VecHelper.h>

float VecHelper::sideOfPoint(glm::vec2 a, glm::vec2 b, glm::vec2 p)
{
	glm::vec2 edgeDirection = b - a;
	glm::vec2 pointDirection = p - a;
	
	return edgeDirection.x * pointDirection.y - edgeDirection.y * pointDirection.x;
}