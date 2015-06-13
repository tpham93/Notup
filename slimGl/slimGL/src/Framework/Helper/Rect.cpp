/********************************************************************************************** 
* 										include
**********************************************************************************************/
#include <Framework/Helper/Rect.h>

/********************************************************************************************** 
* 										class definition
**********************************************************************************************/

Rect::Rect(float x, float y, float width, float height)
	:m_x(x),
	m_y(y),
	m_width(width),
	m_height(height)
{

}

Rect::Rect(glm::vec2 topLeft, glm::vec2 bottomRight)
	: Rect(topLeft.x, topLeft.y, bottomRight.x - topLeft.x, bottomRight.y - topLeft.y)
{

}

bool Rect::intersects(const Rect &rect)
{
	return m_x < rect.m_x + rect.m_width
		  &&m_x + m_width > rect.m_x
		  &&m_y < rect.m_y + rect.m_height
		  &&m_y + m_height > rect.m_y;
}

float Rect::getX() const
{
	return m_x;
}

void Rect::setX(float x)
{
	m_x = x;
}

float Rect::getY() const
{
	return m_y;
}

void Rect::setY(float y)
{
	m_y = y;
}

float Rect::getWidth() const
{
	return m_width;
}

void Rect::setWidth(float width)
{
	m_width = width;
}

float Rect::getHeight() const
{
	return m_height;
}

void Rect::setHeight(float height)
{
	m_height = height;
}

glm::vec2 Rect::getCenter() const
{
	return glm::vec2(m_x + m_width*  0.5f, m_y + 0.5*  m_height);
}