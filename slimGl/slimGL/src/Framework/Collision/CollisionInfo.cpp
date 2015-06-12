#include <Framework/Collision/CollisionInfo.h>

CollisionInfo::CollisionInfo(Shape& shape1, Shape& shape2)
	:m_shape1(shape1),
	m_shape2(shape2),
	m_collides(false),
	m_mtv(0),
	m_distance(0)
{

}

CollisionInfo::CollisionInfo(Shape& shape1, Shape& shape2, glm::vec2 &mtv, float distance)
	:m_shape1(shape1),
	m_shape2(shape2),
	m_collides(true),
	m_mtv(mtv),
	m_distance(distance)
{

}

const Shape& CollisionInfo::getShape1() const
{
	return m_shape1;
}

const Shape& CollisionInfo::getShape2() const
{
	return m_shape2;
}

bool CollisionInfo::isColliding() const
{
	return m_collides;
}

const glm::vec2& CollisionInfo::getMtv() const
{
	return m_mtv;
}

float CollisionInfo::getDistance() const
{
	return m_distance;
}