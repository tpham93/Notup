
/********************************************************************************************** 
* 										includes
**********************************************************************************************/
#include <Framework/Shader/ShaderAttributes.h>

/********************************************************************************************** 
* 										class declaration
**********************************************************************************************/


ShaderAttributes::ShaderAttributes(GLint attributeLocation, GLsizei stride, GLint type, GLint size, const GLvoid* dataptr)
	:m_attributeLocation(attributeLocation),
	m_stride(stride),
	m_type(type),
	m_size(size),
	m_dataptr(dataptr)
{
}

GLint ShaderAttributes::getAttributeLocation() const
{
	return m_attributeLocation;
}

GLsizei ShaderAttributes::getStride() const
{
	return m_stride;
}

GLint ShaderAttributes::getType() const
{
	return m_type;
}

GLint ShaderAttributes::getSize() const
{
	return m_size;
}

const GLvoid*   ShaderAttributes::getDataptr() const
{
	return m_dataptr;
}