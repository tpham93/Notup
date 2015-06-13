/**********************************************************************************************
* 										include
**********************************************************************************************/
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <Framework/Drawable/Sprite.h>
#include <Framework/Shader/ShaderProgram.h>

/**********************************************************************************************
* 										class definition
**********************************************************************************************/


Sprite::Sprite()
	:Sprite(nullptr)
{

}

Sprite::Sprite(std::shared_ptr<const Texture> texture)
	: Drawable(),
	m_texture(texture),
	m_destination(0.0f, 0.0f, (texture == nullptr) ? 0.0f : static_cast<float>(texture->getWidth()), (texture == nullptr) ? 0.0f : static_cast<float>(texture->getHeight())),
	m_source(0.0f, 0.0f, (texture == nullptr) ? 0.0f : static_cast<float>(texture->getWidth()), (texture == nullptr) ? 0.0f : static_cast<float>(texture->getHeight())),
	m_rotation(0.0f),
	m_origin(0.0f)
{

}

const Texture &Sprite::getTexture() const
{
	return*m_texture;
}

void Sprite::setTexture(std::shared_ptr<Texture> texture)
{
	m_texture = texture;

	if (texture != nullptr  && m_texture != nullptr)
	{
		setDestination(Rect(m_destination.getX(), m_destination.getY(), static_cast<float>(m_texture->getWidth()), static_cast<float>(m_texture->getHeight())));
		setSource(Rect(0.0f, 0.0f, static_cast<float>(m_texture->getWidth()), static_cast<float>(m_texture->getHeight())));

		m_vertices[0].m_position = glm::vec2(m_destination.getX(), m_destination.getY());
		m_vertices[1].m_position = m_vertices[0].m_position + glm::vec2(m_destination.getWidth(), 0.0f);
		m_vertices[2].m_position = m_vertices[0].m_position + glm::vec2(m_destination.getWidth(), m_destination.getHeight());
		m_vertices[3].m_position = m_vertices[0].m_position + glm::vec2(0.0f, m_destination.getHeight());
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferData.vertexBufferId);
		glBufferSubData(GL_ARRAY_BUFFER, offsetof(Vertex2DTex, m_position), 4 * sizeof(Vertex2DTex), m_vertices);
	}
}

void Sprite::setOrigin(glm::vec2 origin, bool update)
{
	m_origin = origin;
	if (update)
	{
		updateMatrices();
	}
}

const glm::vec2 &Sprite::getOrigin() const
{
	return m_origin;
}

void Sprite::setDestination(Rect destination, bool update)
{
	// set the new destination
	m_destination = destination;

	if (update)
	{
		updateMatrices();
	}
}

Rect &Sprite::getDestination()
{
	return m_destination;
}

const Rect &Sprite::getDestination() const
{
	return m_destination;
}

void Sprite::setDestination(glm::vec2 position, bool update)
{
	setDestination(Rect(position.x, position.y, m_destination.getWidth(), m_destination.getHeight()), update);
}

Rect &Sprite::getSource()
{
	return m_source;
}

const Rect &Sprite::getSource() const
{
	return m_source;
}

void Sprite::setSource(Rect &source)
{
	m_source = source;

	float sourceWidth = m_source.getWidth() / m_texture->getWidth();
	float sourceHeight = m_source.getHeight() / m_texture->getHeight();
	m_vertices[0].m_texCoord = glm::vec2(m_source.getX() / m_texture->getWidth(), m_source.getY() / m_texture->getHeight());
	m_vertices[1].m_texCoord = m_vertices[0].m_texCoord + glm::vec2(sourceWidth, 0.0f);
	m_vertices[2].m_texCoord = m_vertices[0].m_texCoord + glm::vec2(sourceWidth, sourceHeight);
	m_vertices[3].m_texCoord = m_vertices[0].m_texCoord + glm::vec2(0.0f, sourceHeight);
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferData.vertexBufferId);
	glBufferSubData(GL_ARRAY_BUFFER, offsetof(Vertex2DTex, m_position), 4 * sizeof(Vertex2DTex), m_vertices);
}


void Sprite::setRotation(float rotation, bool update)
{
	m_rotation = rotation;
	if (update)
	{
		updateMatrices();
	}
}

float Sprite::getRotation() const
{
	return m_rotation;
}

void Sprite::initialize()
{
	// create the initial data for the buffer
	m_vertices[0].m_position = glm::vec2(m_destination.getX(), m_destination.getY());
	m_vertices[1].m_position = m_vertices[0].m_position + glm::vec2(m_destination.getWidth(), 0.0f);
	m_vertices[2].m_position = m_vertices[0].m_position + glm::vec2(m_destination.getWidth(), m_destination.getHeight());
	m_vertices[3].m_position = m_vertices[0].m_position + glm::vec2(0.0f, m_destination.getHeight());


	float sourceWidth = 0.0f;
	float sourceHeight = 0.0f;

	if (m_texture != nullptr)
	{
		sourceWidth = m_source.getWidth() / m_texture->getWidth();
		sourceWidth = m_source.getHeight() / m_texture->getHeight();
	}

	m_vertices[0].m_texCoord = glm::vec2(m_source.getX(), m_source.getY());
	m_vertices[1].m_texCoord = m_vertices[0].m_texCoord + glm::vec2(sourceWidth, 0.0f);
	m_vertices[2].m_texCoord = m_vertices[0].m_texCoord + glm::vec2(sourceWidth, sourceHeight);
	m_vertices[3].m_texCoord = m_vertices[0].m_texCoord + glm::vec2(0.0f, sourceHeight);

	GLuint indices[6] = { 0, 3, 1, 2, 1, 3 };

	// creating buffers
	glGenBuffers(1, &m_bufferData.vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferData.vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex2DTex), m_vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &m_bufferData.indexBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferData.indexBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), indices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &m_bufferData.vertexArrayId);

	glBindBuffer(GL_ARRAY_BUFFER, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
}

void Sprite::draw()
{
	// check if the texture is set
	assert(m_texture != nullptr  &&"texture has to be set!");

	m_shaderProgram->use();
	m_shaderProgram->getMatrixHandler().pushMatrix("modelMatrix");
	glm::mat4& modelMatrix = m_shaderProgram->getMatrixHandler().getMatrix("modelMatrix");
	modelMatrix *= m_modelMatrix;
	m_shaderProgram->updateMatrix("modelMatrix");

	m_texture->bind();
	glBindVertexArray(m_bufferData.vertexArrayId);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(NULL);

	m_shaderProgram->getMatrixHandler().popMatrix("modelMatrix");
	m_shaderProgram->updateMatrix("modelMatrix");
	modelMatrix = m_shaderProgram->getMatrixHandler().getMatrix("modelMatrix");
}

void Sprite::updateMatrices()
{
	glm::vec2 scale(m_destination.getWidth() / m_texture->getWidth(), m_destination.getHeight() / m_texture->getHeight());
	glm::vec2 pos(m_destination.getX(), m_destination.getY());
	m_modelMatrix = glm::mat4();
	m_modelMatrix = glm::translate(m_modelMatrix, glm::vec3(pos, 0.0f));
	m_modelMatrix = glm::rotate(m_modelMatrix, m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(scale, 1.0f));
	m_modelMatrix = glm::translate(m_modelMatrix, -glm::vec3(m_origin, 0.0f));
}