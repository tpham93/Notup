#pragma once

/**********************************************************************************************
* 										includes
**********************************************************************************************/
#include <string>
#include <GL/glew.h>

/**********************************************************************************************
* 										class declaration
**********************************************************************************************/

/*!
* 	\brief			collecting the info about the source type
*/
class Shader
{
public:
	/*!
	* 	\brief	copies are not allowed!
	*/
	Shader(const Shader &shader) = delete;

	/*!
	* 	\brief	assignments aren't allowed!
	*/
	Shader &operator=(const Shader &shader) = delete;

	/*!
	* 	\brief				constructor
	* 	\param filepath		the path to the source file
	* 	\param shaderType	the type of shader
	*/
	Shader(std::string filepath, GLenum shaderType);

	/*!
	* 	\brief				destructor
	* 	\pre				none
	* 	\post				deletes the shader from the gpu if it was compiled
	*/
	virtual ~Shader();

	/*!
	* 	\brief				destructor
	* 	\pre				the shader is compiled already
	* 	\post				deletes the shader from the gpu
	*/
	void free();

	/*!
	* 	\brief				compiles the sourcefile of the shader
	* 	\pre				shader is not compiled yet
	* 	\post				shader is compiled on the gpu
	*/
	bool compile();

	/*!
	* 	\brief			gets the filepath
	*/
	std::string getFilepath() const;


	/*!
	* 	\brief			gets the shader type
	*/
	GLenum getShaderType() const;

	/*!
	* 	\brief			gets the shader id
	* 	\return			0 if the shader is not compiled, otherwise the id of the shader
	*/
	GLint getShaderId() const;

private:
	//! the path to the source file
	std::string m_filepath;

	//! the type of shader
	GLenum m_shaderType;

	//! the id of the shader on the gpu
	GLint m_shaderId;
};
