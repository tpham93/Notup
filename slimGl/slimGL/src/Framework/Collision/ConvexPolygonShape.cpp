#include <Framework/Collision/ConvexPolygonShape.h>

#include <Framework/Collision/CircleShape.h>
#include <algorithm>
#include <limits>

ConvexPolygonShape::ConvexPolygonShape(glm::vec2 position, std::vector<glm::vec2> &vertices)
	:Shape(0, position),
	m_originalVertices(vertices),
	m_originalEdges(),
	m_rotatedVertices(),
	m_edges()
{
	float maxDistanceSq = -std::numeric_limits<float>::infinity();
	for (unsigned int i = 0; i < vertices.size(); ++i)
	{
		int j = (i + 1) % vertices.size();
		glm::vec2 currentEdge = vertices[i] - vertices[j];
		bool missing = true;

		maxDistanceSq = std::max(maxDistanceSq, glm::dot(vertices[i], vertices[i]));
		
		m_vertices.push_back(vertices[i] + position);
		currentEdge = glm::normalize(currentEdge);
		if (currentEdge.x < 0 || (currentEdge.x == 0 && currentEdge.y < 0))
		{
			currentEdge *= -1;
		}
		for (unsigned int k = 0; k < m_edges.size(); ++k)
		{
			missing &= !(currentEdge == m_edges[k]);
		}

		if (missing)
		{
			m_edges.push_back(currentEdge);
		}
	}
	m_rotatedVertices = vertices;
	m_originalEdges = m_edges;
	m_radius = static_cast<float>(std::sqrt(maxDistanceSq));


}

ShapeType ConvexPolygonShape::getShapeType() const
{
	return ShapeType::ConvexPolygon;
}

CollisionInfo ConvexPolygonShape::collide(Shape& shape)
{
	glm::vec2 distance = shape.getPosition() - m_position;
	float realDistSq = glm::dot(distance, distance);
	float maxDistSq = (m_radius + shape.getRadius()) * (m_radius + shape.getRadius());
	if (realDistSq < maxDistSq)
	{
		switch (shape.getShapeType())
		{
		case ShapeType::Circle:
			return collide(static_cast<CircleShape&>(shape));
			break;
		case ShapeType::ConvexPolygon:
			return collide(static_cast<ConvexPolygonShape&>(shape));
			break;
		case ShapeType::ConcavPolygon:
			break;
		}
	}
	return CollisionInfo(*this, shape);
}

CollisionInfo ConvexPolygonShape::collide(CircleShape& shape)
{
	float minIntersection = std::numeric_limits<float>::infinity();
	glm::vec2 mtv;
	for (unsigned int i = 0; i < m_edges.size(); ++i)
	{
		Range range1 = project(m_edges[i]);
		Range range2 = Range(glm::dot(m_edges[i], shape.getPosition()) - shape.getRadius(), glm::dot(m_edges[i], shape.getPosition()) + shape.getRadius());
		float intersection = range1.intersection(range2);
		if (intersection > 0)
		{
			if (minIntersection > intersection)
			{
				minIntersection = intersection;
				mtv = glm::vec2(m_edges[i].y, m_edges[i].x);
			}
		}
		else
		{
			return CollisionInfo(*this, shape);
		}
	}
	for (unsigned int i = 0; i < m_vertices.size(); ++i)
	{
		glm::vec2 normalizedPossibleMtv = glm::normalize(shape.getPosition() - m_vertices[i]);
		Range range1 = project(normalizedPossibleMtv);
		Range range2 = Range(glm::dot(normalizedPossibleMtv, shape.getPosition()) - shape.getRadius(), glm::dot(normalizedPossibleMtv, shape.getPosition()) + shape.getRadius());
		float intersection = range1.intersection(range2);
		if (intersection > 0)
		{
			if (minIntersection > intersection)
			{
				minIntersection = intersection;
				mtv = glm::vec2(m_edges[i].y, m_edges[i].x);
			}
		}
		else
		{
			return CollisionInfo(*this, shape);
		}
	}

	if (glm::dot(mtv, shape.getPosition() - m_position))
	{
		mtv *= -1;
	}

	return CollisionInfo(*this, shape, glm::normalize(mtv), minIntersection);
}

CollisionInfo ConvexPolygonShape::collide(ConvexPolygonShape& shape)
{
	float minIntersection = std::numeric_limits<float>::infinity();
	glm::vec2 mtv;
	for (unsigned int i = 0; i < m_edges.size(); ++i)
	{
		Range range1 = project(m_edges[i]);
		Range range2 = shape.project(m_edges[i]);
		float intersection = range1.intersection(range2);
		if (intersection > 0)
		{
			if (minIntersection > intersection)
			{
				minIntersection = intersection;
				mtv = glm::vec2(m_edges[i].y, m_edges[i].x);
			}
		}
		else
		{
			return CollisionInfo(*this, shape);
		}
	}
	for (unsigned int i = 0; i < shape.m_edges.size(); ++i)
	{
		Range range1 = project(shape.m_edges[i]);
		Range range2 = shape.project(shape.m_edges[i]);
		float intersection = range1.intersection(range2);
		if (intersection > 0)
		{
			if (minIntersection > intersection)
			{
				minIntersection = intersection;
				mtv = glm::vec2(m_edges[i].y, m_edges[i].x);
			}
		}
		else
		{
			return CollisionInfo(*this, shape);
		}
	}

	if (glm::dot(mtv, shape.getPosition() - m_position))
	{
		mtv *= -1;
	}

	return CollisionInfo(*this, shape, glm::normalize(mtv), minIntersection);
}

void ConvexPolygonShape::setRotation(float rotation)
{
	float cosRotation = glm::cos(rotation);
	float sinRotation = glm::sin(rotation);
	for (unsigned int i = 0; i < m_rotatedVertices.size(); ++i)
	{
		m_rotatedVertices[i] = glm::vec2(cosRotation * m_originalVertices[i].x - sinRotation * m_originalVertices[i].y, sinRotation * m_originalVertices[i].x + cosRotation * m_originalVertices[i].y);
		m_vertices[i] = m_rotatedVertices[i] + m_position;
	}
	m_rotation = rotation;

	m_edges.clear();
	for (unsigned int i = 0; i < m_rotatedVertices.size(); ++i)
	{
		int j = (i + 1) % m_rotatedVertices.size();
		glm::vec2 currentEdge = m_rotatedVertices[i] - m_rotatedVertices[j];
		bool missing = true;
		currentEdge = glm::normalize(currentEdge);
		if (currentEdge.x < 0 || (currentEdge.x == 0 && currentEdge.y < 0))
		{
			currentEdge *= -1;
		}
		for (unsigned int k = 0; k < m_edges.size(); ++k)
		{
			missing &= !(currentEdge == m_edges[k]);
		}

		if (missing)
		{
			m_edges.push_back(currentEdge);
		}
	}
}

void ConvexPolygonShape::setPosition(glm::vec2 position)
{
	for (unsigned int i = 0; i < m_rotatedVertices.size(); ++i)
	{
		m_vertices[i] = m_rotatedVertices[i] + position;
	}
	m_position = position;
}

Range ConvexPolygonShape::project(const glm::vec2 &edge)
{
	Range finalRange;
	for (unsigned int i = 0; i < m_vertices.size(); ++i)
	{
		finalRange.add(glm::dot(edge,m_vertices[i]));
	}
	return finalRange;
}