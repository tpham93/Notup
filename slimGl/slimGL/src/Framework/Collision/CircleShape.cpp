#include <Framework/Collision/CircleShape.h>

CircleShape::CircleShape(float radius, glm::vec2 position)
	:Shape(radius, position)
{

}

ShapeType CircleShape::getShapeType() const
{
	return ShapeType::Circle;
}

CollisionInfo CircleShape::collide(Shape& shape)
{

	if (shape.getShapeType() == ShapeType::Circle)
	{
		return collide(static_cast<CircleShape&>(shape));
	}
	else
	{
		glm::vec2 distance = shape.getPosition() - m_position;
		float realDistSq = glm::dot(distance, distance);
		float maxDistSq = (m_radius + shape.getRadius()) * (m_radius + shape.getRadius());
		if (realDistSq < maxDistSq)
		{
			switch (shape.getShapeType())
			{
			case ShapeType::ConcavPolygon:
				break;
			case ShapeType::ConvexPolygon:
				break;
			}
		}
	}
	return CollisionInfo(*this, shape);
}


CollisionInfo CircleShape::collide(CircleShape& shape)
{
	glm::vec2 distance = shape.getPosition() - m_position;
	float realDistSq = glm::dot(distance, distance);
	float maxDistSq = (m_radius + shape.getRadius()) * (m_radius + shape.getRadius());
	if (realDistSq < maxDistSq)
	{
		glm::vec2 mtv = m_position - shape.getPosition();
		float distance = glm::length(mtv);
		mtv /= distance;
		distance = m_radius + shape.getRadius() - distance;
		return CollisionInfo(*this, shape, mtv/distance, distance);
	}
	else
	{
		return CollisionInfo(*this, shape);
	}
}