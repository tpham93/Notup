/**********************************************************************************************
* 										include
**********************************************************************************************/
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
	m_source(0.0f, 0.0f, (texture == nullptr) ? 0.0f : static_cast<float>(texture->getWidth()), (texture == nullptr) ? 0.0f : static_cast<float>(texture->getHeight()))
{

}

const Texture &Sprite::getTexture() const
{
	return*m_texture;
}
#include <Framework/Helper/Helper.h>
void Sprite::setTexture(std::shared_ptr<Texture> texture)
{
	m_texture = texture;

	if (texture != nullptr  && m_texture != nullptr)
	{
		setDestination(Rect(m_destination.getX(), m_destination.getY(), static_cast<float>(m_texture->getWidth()), static_cast<float>(m_texture->getHeight())));
		setSource(Rect(0.0f, 0.0f, static_cast<float>(m_texture->getWidth()), static_cast<float>(m_texture->getHeight())));
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

void Sprite::setDestination(Rect destination)
{
	// set the new destination
	m_destination = destination;


	m_vertices[0].m_position = glm::vec2(m_destination.getX(), m_destination.getY());
	m_vertices[1].m_position = m_vertices[0].m_position + glm::vec2(m_destination.getWidth(), 0.0f);
	m_vertices[2].m_position = m_vertices[0].m_position + glm::vec2(m_destination.getWidth(), m_destination.getHeight());
	m_vertices[3].m_position = m_vertices[0].m_position + glm::vec2(0.0f, m_destination.getHeight());

	glBindBuffer(GL_ARRAY_BUFFER, m_bufferData.vertexBufferId);
	if (!Helper::checkGlForError(std::cout, "OpenGlA6 Error"))
	{
		std::cout << "blah" << std::endl;
	}
	glBufferSubData(GL_ARRAY_BUFFER, offsetof(Vertex2DTex, m_position), 4 * sizeof(Vertex2DTex), m_vertices);
	Helper::checkGlForError(std::cout, "OpenGlA5 Error");
}

void Sprite::setDestination(glm::vec2 position)
{
	setDestination(Rect(position.x, position.y, m_destination.getWidth(), m_destination.getHeight()));
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
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex2DTex), m_vertices, GL_DYNAMIC_DRAW);

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

	Helper::checkGlForError(std::cout, "OpenGlA3 Error");
	m_shaderProgram->use();
	m_texture->bind();
	glBindVertexArray(m_bufferData.vertexArrayId);

	Helper::checkGlForError(std::cout, "OpenGlA2 Error");
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(NULL);
	Helper::checkGlForError(std::cout, "OpenGlA1 Error");

}