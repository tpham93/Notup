#pragma once

/**********************************************************************************************
* 										includes
**********************************************************************************************/
#include <Framework/Resources/Texture.h>
#include <Framework/Shader/ShaderProgram.h>
#include <Framework/UniformStruct/Material/TextureMaterial.h>

/**********************************************************************************************
* 										class declaration
**********************************************************************************************/

/*!
* 	\brief	a very basic material to use with lighting shader
*/
class BasicLightingMaterial : public TextureMaterial
{
public:
	/*!
	* 	\brief	constructor
	*/
	BasicLightingMaterial();

	/*!
	* 	\brief	destructor
	*/
	virtual ~BasicLightingMaterial();

	/*!
	* 	\brief				set emission
	* 	\param emission		the new value for emission
	*/
	void setEmission(glm::vec4 &emission);

	/*!
	* 	\brief				set diffuse
	* 	\param emission		the new value for diffuse
	*/
	void setDiffuse(glm::vec4 &diffuse);

	/*!
	* 	\brief				set ambient
	* 	\param emission		the new value for ambient
	*/
	void setAmbient(glm::vec4 &ambient);

	/*!
	* 	\brief				set specular
	* 	\param emission		the new value for specular
	*/
	void setSpecular(glm::vec4 &specular);

	/*!
	* 	\brief				set shininess
	* 	\param emission		the new value for shininess
	*/
	void setShininess(float shininess);

	/*!
	* 	\brief					binds the material to the shader program
	* 	\param shaderProgram	the shader program where the material should be bound to
	* 	\pre					the shader program is compiled and linked
	* 	\post					the shader program uses the material in the next draw calls
	*/
	virtual void sendToShaderProgram(const std::string &name, ShaderProgram &shaderProgram) const override;
private:
	//!	emission color
	glm::vec4 m_emission;
	//! diffuse color
	glm::vec4 m_diffuse;
	//! ambient color
	glm::vec4 m_ambient;
	//! specular color
	glm::vec4 m_specular;
	//! the shininess
	float m_shininess;
};
