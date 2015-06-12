/********************************************************************************************** 
* 										include
**********************************************************************************************/
#include <Framework/Drawable/Drawable.h>
#include <Framework/Shader/ShaderProgram.h>

/********************************************************************************************** 
* 										class definition
**********************************************************************************************/


Drawable::Drawable()
	:m_bufferData(),
	m_shaderProgram(nullptr)
{

}

Drawable::~Drawable()
{
	if (m_bufferData.vertexArrayId != 0)
	{
		glDeleteBuffers(1, &m_bufferData.vertexArrayId);
		m_bufferData.vertexArrayId = 0;
	}
	if (m_bufferData.indexBufferId != 0)
	{
		glDeleteBuffers(1, &m_bufferData.indexBufferId);
		m_bufferData.indexBufferId = 0;
	}
	if (m_bufferData.vertexBufferId != 0)
	{
		glDeleteBuffers(1, &m_bufferData.vertexBufferId);
		m_bufferData.vertexBufferId = 0;
	}
}

void Drawable::setShaderProgram(std::shared_ptr<ShaderProgram> shaderProgram)
{
	if (shaderProgram != m_shaderProgram)
	{
		// set the pointer for the shader program
		m_shaderProgram = shaderProgram;
		// binding the buffer
		glBindVertexArray(m_bufferData.vertexArrayId);
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferData.vertexBufferId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferData.indexBufferId);
		// enable and set the attrib pointer
		shaderProgram->use();
		shaderProgram->enableAttribPointer();
		shaderProgram->setAttributePointer();
		// unbind the vertex array
		glBindVertexArray(NULL);
	}
}