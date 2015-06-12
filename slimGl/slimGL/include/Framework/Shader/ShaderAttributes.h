#pragma once

/**********************************************************************************************
* 										includes
**********************************************************************************************/
#include <GL/glew.h>

/**********************************************************************************************
* 										class declaration
**********************************************************************************************/

/*!
* 	\brief a class to group the location, stride and pointer to an attribute
*/
class ShaderAttributes
{
public:

	/*!
	* 	\brief						constructor
	* 	\param attributeLocation	the location of the attribute
	* 	\param stride				the stride of the attribute
	* 	\param type					the type of the attribute
	* 	\param size					the number of type in the attribute
	* 	\param dataptr				the pointer to the data of the attribute
	*/
	ShaderAttributes(GLint attributeLocation, GLsizei stride, GLint type, GLint size, const GLvoid* dataptr);

	/*!
	* 	\brief			gets the location of the attribute
	* 	\return			the location of the attribute
	*/
	GLint getAttributeLocation() const;

	/*!
	* 	\brief			gets the stride for the attribute
	* 	\return			the stride of the attribute
	*/
	GLsizei getStride() const;

	/*!
	* 	\brief			gets the type of the attribute
	* 	\return			the type of the attribute
	*/
	GLint getType() const;

	/*!
	* 	\brief			gets the type of the attribute
	* 	\return			the type of the attribute
	*/
	GLint getSize() const;

	/*!
	* 	\brief			gets the pointer to the data of the pointer
	* 	\return			the pointer to the data of the attribute
	*/
	const GLvoid*  getDataptr() const;
private:
	//! the location of the attribute
	GLint m_attributeLocation;
	//! the stride of the attribute
	GLsizei m_stride;
	//! the type of the attribute
	GLint m_type;
	//! the number of m_types in the attribute
	GLint m_size;
	//! the pointer to the attribute
	const GLvoid* m_dataptr;
};
