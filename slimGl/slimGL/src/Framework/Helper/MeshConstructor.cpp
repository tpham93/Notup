#include <Framework/Helper/MeshConstructor.h>

#include <algorithm>
#include <set>

std::shared_ptr<Mesh<Vertex3DNormTex>> MeshConstructor::constructBoundingBoxMesh(const Box &box)
{
	std::shared_ptr<Mesh<Vertex3DNormTex>> mesh(std::make_shared<Mesh<Vertex3DNormTex>>());
	std::vector<Vertex3DNormTex> vertices;
	std::vector<GLuint> indices;
	std::vector<glm::vec3> positions;

	for (int i = 0; i < 8; ++i)
	{
		int x = std::min(1, i & 1 << 0);
		int y = std::min(1, i & 1 << 1);
		int z = std::min(1, i & 1 << 2);
		positions.push_back(box.getRearBottomLeft() + glm::vec3(x * box.getWidth(), y * box.getHeight(), z * box.getDepth()));
	}
	//								right			top				rear			front			bottom			left
	unsigned int faces[6][4] = { { 5, 1, 3, 7 }, { 6, 7, 3, 2 }, { 1, 0, 2, 3 }, { 4, 5, 7, 6 }, { 0, 1, 5, 4 }, { 0, 4, 6, 2 } };

	for (int faceIndex = 0; faceIndex < 6; ++faceIndex)
	{
		float bottom = 0.5f * static_cast<float>(faceIndex / 3);
		float left = 1.0f / 3.0f * static_cast<float>(faceIndex / 2);
		float height = 0.5f;
		float width = 1.0f / 3.0f;

		int x = std::min(1, (faceIndex + 1) & 1 << 0);
		int y = std::min(1, (faceIndex + 1) & 1 << 1);
		int z = std::min(1, (faceIndex + 1) & 1 << 2);
		if (x + y + z != 0 && x + y + z != 3)
		{
			glm::vec3 normal = glm::vec3(x, y, z);
			if (x + y + z == 2)
			{
				normal -= glm::vec3(1);
			}

			for (int faceCornerIndex = 0; faceCornerIndex < 4; ++faceCornerIndex)
			{
				unsigned int positionIndex = faces[faceIndex][faceCornerIndex];
				Vertex3DNormTex vertex;
				vertex.m_position = positions[positionIndex];
				int texX = std::min(1, faceCornerIndex & 1 << 0);
				int texY = std::min(1, faceCornerIndex & 1 << 1);

				vertex.m_texCoord = glm::vec2(bottom + texX * width, left + texY * height);
				vertex.m_normal = normal;
				vertices.push_back(vertex);
			}
		}

		indices.push_back(4 * faceIndex + 0);
		indices.push_back(4 * faceIndex + 1);
		indices.push_back(4 * faceIndex + 2);

		indices.push_back(4 * faceIndex + 2);
		indices.push_back(4 * faceIndex + 3);
		indices.push_back(4 * faceIndex + 0);
	}

	mesh->addVertex(vertices);
	mesh->setIndices(indices);
	return mesh;
}

std::shared_ptr<Mesh<Vertex3DNormTex>> MeshConstructor::constructConvexPolygonMesh(const std::vector<Vertex3DNormTex> &vertices, const glm::vec3 &axis1, const glm::vec3 &axis2, const glm::vec3 rotation, float accuracy)
{
	std::shared_ptr<Mesh<Vertex3DNormTex>> mesh(std::make_shared<Mesh<Vertex3DNormTex>>());

	glm::mat3x2 projection = glm::transpose(glm::mat2x3(axis1, axis2));
	std::vector<glm::ivec2> positions;
	std::vector<glm::vec2> uniquePositions;
	std::vector<int> convexHullPositions;
	glm::vec2 middlePoint;
	Box meshBounds(glm::vec3(std::numeric_limits<float>::infinity()), -glm::vec3(std::numeric_limits<float>::infinity()));
	int startPointIndex = 0;
	int nextPointIndex = 0;

	glm::mat4 transformation(1);
	transformation = glm::rotate(transformation, rotation.x, glm::vec3(1, 0, 0));
	transformation = glm::rotate(transformation, rotation.y, glm::vec3(0, 1, 0));
	transformation = glm::rotate(transformation, rotation.z, glm::vec3(0, 0, 1));

	std::vector<glm::vec2> boundVertices;
	for (int i = 0; i < 4; ++i)
	{
		boundVertices.push_back(projection * glm::vec3(transformation * glm::vec4(vertices[0].m_position, 1)));
	}

	for (unsigned int vertexIndex = 0; vertexIndex < vertices.size(); ++vertexIndex)
	{
		glm::vec2 projectedPosition = projection * glm::vec3(transformation * glm::vec4(vertices[vertexIndex].m_position, 1));
		if (boundVertices[0].x > projectedPosition.x)
		{
			boundVertices[0] = projectedPosition;
		}
		if (boundVertices[1].y > projectedPosition.y)
		{
			boundVertices[1] = projectedPosition;
		}
		if (boundVertices[2].x < projectedPosition.x)
		{
			boundVertices[2] = projectedPosition;
		}
		if (boundVertices[3].y < projectedPosition.y)
		{
			boundVertices[3] = projectedPosition;
		}
	}

	meshBounds = Box(glm::vec3(boundVertices[0].x, boundVertices[1].y, 0),glm::vec3(boundVertices[2].x, boundVertices[3].y, 0));

	for (int i = 0; i < 4; ++i)
	{
		glm::vec2 projectedPosition = boundVertices[i];
		glm::ivec2 scaledPosition = glm::ivec2(boundVertices[i] * accuracy);
		if (std::find(positions.begin(), positions.end(), scaledPosition) == positions.end())
		{
			positions.push_back(scaledPosition);
		}
		uniquePositions.push_back(projectedPosition);
		middlePoint += projectedPosition;
	}

	for (unsigned int vertexIndex = 0; vertexIndex < vertices.size(); ++vertexIndex)
	{
		glm::vec2 projectedPosition = projection * glm::vec3(transformation * glm::vec4(vertices[vertexIndex].m_position, 1));
		glm::ivec2 scaledPosition = glm::ivec2(projectedPosition * accuracy);
		if (std::find(positions.begin(), positions.end(), scaledPosition) == positions.end())
		{
			positions.push_back(scaledPosition);
			uniquePositions.push_back(projectedPosition);
			middlePoint += projectedPosition;
		}
	}

	middlePoint /= uniquePositions.size();
	std::sort(uniquePositions.begin(), uniquePositions.end(), [](const glm::vec2& a, const glm::vec2& b) { return a.x < b.x; });

	bool firstRun = true;
	while (nextPointIndex != startPointIndex || firstRun)
	{
		firstRun = false;
		unsigned int pI1 = nextPointIndex;
		glm::vec2 &p1(uniquePositions[pI1]);
		bool foundExtremePoint = false;
		for (unsigned int pI2 = 0; pI2 < uniquePositions.size() && !foundExtremePoint; ++pI2)
		{
			if (pI1 != pI2)
			{
				bool extremePoint = true;
				glm::vec2 &p2(uniquePositions[pI2]);
				for (unsigned int pI3 = 0; pI3 < uniquePositions.size() && extremePoint; ++pI3)
				{
					if (pI1 != pI3 && pI2 != pI3)
					{
						glm::vec2 &p3(uniquePositions[pI3]);
						float side = VecHelper::sideOfPoint(p1, p2, p3);
						if (side >= 0)
						{
							side = VecHelper::sideOfPoint(p1, p2, p3);
							extremePoint = false;
						}
					}
				}
				if (extremePoint)
				{
					convexHullPositions.push_back(pI2);
					nextPointIndex = pI2;
					foundExtremePoint = true;
				}
			}
		}
	}
	convexHullPositions.push_back(static_cast<int>(uniquePositions.size()));
	uniquePositions.push_back(middlePoint);


	std::vector<Vertex3DNormTex> meshVertices;
	std::vector<GLuint> indices;
	glm::vec3 invAxis1(axis1.x == 0 ? 0.0f : 1.0f / axis1.x, axis1.y == 0 ? 0.0f : 1.0f / axis1.y, axis1.z == 0 ? 0.0f : 1.0f / axis1.z);
	glm::vec3 invAxis2(axis2.x == 0 ? 0.0f : 1.0f / axis2.x, axis2.y == 0 ? 0.0f : 1.0f / axis2.y, axis2.z == 0 ? 0.0f : 1.0f / axis2.z);
	glm::mat2x3 projectionToWorld(invAxis1, invAxis2);
	glm::vec3 normal(-glm::cross(axis1, axis2));
	for (unsigned int convexHullPositionIndex = 0; convexHullPositionIndex < convexHullPositions.size(); ++convexHullPositionIndex)
	{
		glm::vec2 position = uniquePositions[convexHullPositions[convexHullPositionIndex]];

		Vertex3DNormTex vertex;
		vertex.m_position = projectionToWorld * position;
		vertex.m_texCoord = glm::vec2((static_cast<float>(position.x) - meshBounds.getX()) / meshBounds.getWidth(), (static_cast<float>(position.y) - meshBounds.getY()) / meshBounds.getHeight());
		vertex.m_normal = normal;
		meshVertices.push_back(vertex);

		if (convexHullPositionIndex < convexHullPositions.size() - 1)
		{
			indices.push_back(convexHullPositionIndex);
			indices.push_back((convexHullPositionIndex + 1) % (static_cast<int>(convexHullPositions.size()) - 1));
			indices.push_back(static_cast<int>(convexHullPositions.size()) - 1);
		}
	}

	mesh->addVertex(meshVertices);
	mesh->setIndices(indices);
	return mesh;
}