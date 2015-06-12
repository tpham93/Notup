#pragma once

/********************************************************************************************** 
* 										includes
**********************************************************************************************/
#include <Framework/Shader/ShaderProgram.h>

/********************************************************************************************** 
* 										class declaration
**********************************************************************************************/

/*!
* 	\brief	a base class for all used materials
*/
class UniformStruct
{
public:
	/*!
	* 	\brief	constructor
	*/
	UniformStruct();

	/*!
	* 	\brief	destructor
	*/
	virtual ~UniformStruct();

	/*!
	* 	\brief					binds the struct to the shader program
	* 	\param shaderProgram	the shader program where the uniform struct should be bound to
	* 	\pre					the shader program is compiled and linked
	* 	\post					the shader program uses the material in the next draw calls
	*/
	virtual void sendToShaderProgram(const std::string &name, ShaderProgram &shaderProgram) const = 0;
};
