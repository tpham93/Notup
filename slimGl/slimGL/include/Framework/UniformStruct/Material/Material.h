#pragma once

/********************************************************************************************** 
* 										includes
**********************************************************************************************/
#include <Framework/Shader/ShaderProgram.h>
#include <Framework/UniformStruct/UniformStruct.h>

/********************************************************************************************** 
* 										class declaration
**********************************************************************************************/

/*!
* 	\brief	a base class for all used materials
*/
class Material : public UniformStruct
{
public:
	/*!
	* 	\brief	constructor
	*/
	Material();

	/*!
	* 	\brief	destructor
	*/
	virtual ~Material();

	/*!
	* 	\brief					binding the material to the shader program
	* 								uses sendToShadrProgram(ShaderProgram &shaderProgram) const
	* 	\param shaderProgram	the shader program where the material should be bound to
	* 	\pre					the shader program is compiled and linked
	* 	\post					the shader program uses the material in the next draw calls
	*/
	void bind(const std::string &name, ShaderProgram &shaderProgram) const;

private:
	/*!
	* 	\brief					binding the ressources used for the material to the shader program
	* 								uses sendToShadrProgram(ShaderProgram &shaderProgram) const
	* 	\param shaderProgram	the shader program where the material should be bound to
	*/
	virtual void bindRessources(const std::string &name, ShaderProgram &shaderProgram) const;

	//! the last id assigned to a material
	static unsigned int lastAssignedMaterialId;
	//! the current bound material (0 if there is none bound)
	static unsigned int currentBoundMaterialId;
	//! the id of the material
	unsigned int m_materialId;
};