/********************************************************************************************** 
* 										includes
**********************************************************************************************/
#include <Framework/Drawable/Mesh.t>

/********************************************************************************************** 
* 										class definition
**********************************************************************************************/



template<typename VertexType>
Mesh<VertexType>::Mesh()
	:Drawable(),
	m_vertices(),
	m_indices(),
	m_numVertices(0),
	m_numIndices(0),
	m_boundingBox(glm::vec3(std::numeric_limits<float>::infinity()), -glm::vec3(std::numeric_limits<float>::infinity()))
{
}

template<typename VertexType>
void Mesh<VertexType>::initialize()
{
	glGenVertexArrays(1, &m_bufferData.vertexArrayId);
	glGenBuffers(1, &m_bufferData.vertexBufferId);
	glGenBuffers(1, &m_bufferData.indexBufferId);
}

template<typename VertexType>
void Mesh<VertexType>::addVertex(const VertexType &vertex)
{
	m_vertices.push_back(vertex);
	++m_numVertices;
	m_boundingBox = Box(glm::min(m_boundingBox.getRearBottomLeft(), vertex.m_position), glm::max(m_boundingBox.getFrontTopRight(), vertex.m_position));

}


template<typename VertexType>
void Mesh<VertexType>::addVertex(std::vector<VertexType> &vertices)
{
	for (unsigned int i = 0; i < vertices.size(); ++i)
	{
		addVertex(vertices[i]);
	}
}


template<typename VertexType>
void Mesh<VertexType>::setIndices(std::vector<GLuint> indices)
{
	m_indices = indices;
	m_numIndices = static_cast<unsigned int>(indices.size());
}


template<typename VertexType>
void Mesh<VertexType>::uploadData(bool deleteData)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferData.vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, m_numVertices * sizeof(VertexType), reinterpret_cast<GLvoid*>(&m_vertices[0]), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferData.indexBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_numIndices*  sizeof(GLuint), reinterpret_cast<GLvoid*>(&m_indices[0]), GL_STATIC_DRAW);
	if (deleteData)
	{
		deleteLocalData();
	}
}

template<typename VertexType>
void Mesh<VertexType>::deleteLocalData()
{
	m_vertices.clear();
	m_indices.clear();
}

template<typename VertexType>
void Mesh<VertexType>::draw()
{
	m_shaderProgram->use();
	glBindVertexArray(m_bufferData.vertexArrayId);
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferData.vertexBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferData.indexBufferId);
	glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(NULL);
}

template<typename VertexType>
Box Mesh<VertexType>::getBoundingBox()
{
	return m_boundingBox;
}

template<typename VertexType>
const std::vector<VertexType>& Mesh<VertexType>::getVertices() const
{
	return m_vertices;
}

template<typename VertexType>
std::vector<VertexType>& Mesh<VertexType>::getVertices()
{
	return m_vertices;
}

template<typename VertexType>
const std::vector<GLuint>& Mesh<VertexType>::getIndices() const
{
	return m_indices;
}

template<typename VertexType>
std::vector<GLuint>& Mesh<VertexType>::getIndices()
{
	return m_indices;
}