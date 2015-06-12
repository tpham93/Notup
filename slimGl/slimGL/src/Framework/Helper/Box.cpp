#include <Framework/Helper/Box.h>

Box::Box(float x, float y, float z, float width, float height, float depth)
	:Rect(x,y,width,height),
	m_z(z),
	m_depth(depth)
{
}

Box::Box(glm::vec3 rearTopLeft, glm::vec3 frontBottomRight)
	:Box(rearTopLeft.x, rearTopLeft.y, rearTopLeft.z, frontBottomRight.x - rearTopLeft.x, frontBottomRight.y - rearTopLeft.y, frontBottomRight.z - rearTopLeft.z)
{
}

bool Box::intersects(const Box &box)
{
	return m_x <= box.m_x + box.m_width
		&&m_x + m_width >= box.m_x
		&&m_y <= box.m_y + box.m_height
		&&m_y + m_height >= box.m_y
		&&m_z <= box.m_z + box.m_depth
		&&m_z + m_depth >= box.m_z;
}

float Box::getZ() const
{
	return m_z;
}

void Box::setZ(float z)
{
	m_z = z;
}

float Box::getDepth() const
{
	return m_depth;
}

void Box::setDepth(float depth)
{
	m_depth = depth;
}

glm::vec3 Box::getCenter() const
{
	return glm::vec3(m_x + m_width*  0.5f, m_y + 0.5*  m_height, m_z + 0.5 * m_depth);
}

glm::vec3 Box::getRearBottomLeft() const
{
	return glm::vec3(m_x,m_y, m_z);
}

glm::vec3 Box::getFrontTopRight() const
{
	return glm::vec3(m_x + m_width, m_y + m_height, m_z + m_depth);
}