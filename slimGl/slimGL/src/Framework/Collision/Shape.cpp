#include <Framework/Collision/Shape.h>

Shape::Shape(float radius, glm::vec2 position)
	:m_radius(radius),
	m_position(position),
	m_rotation(0.0f)
{

}

float Shape::getRadius() const
{
	return m_radius;
}

glm::vec2 Shape::getPosition() const
{
	return m_position;
}

float Shape::getRotation() const
{
	return m_rotation;
}

void Shape::rotate(float rotation)
{
	setRotation(m_rotation + rotation);
}

void Shape::translate(glm::vec2 movement)
{
	setPosition(m_position + movement);
}

void Shape::setRotation(float rotation)
{
	m_rotation = rotation;
}

void Shape::setPosition(glm::vec2 position)
{
	m_position = position;
}
