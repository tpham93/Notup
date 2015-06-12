#pragma once

/**********************************************************************************************
* 										includes
**********************************************************************************************/
#include <Framework/UniformStruct/UniformStruct.h>

/**********************************************************************************************
* 										class declaration
**********************************************************************************************/

/*!
* 	\brief	a very basic material with just a texture
*/
class PointLight : public UniformStruct
{
public:
	/*!
	* 	\brief	constructor
	*/
	PointLight();

	/*!
	* 	\brief	destructor
	*/
	virtual ~PointLight();

	/*!
	* 	\brief					binds the material to the shader program
	* 	\param shaderProgram	the shader program where the material should be bound to
	* 	\pre					the shader program is compiled and linked
	* 	\post					the shader program uses the material in the next draw calls
	*/
	virtual void sendToShaderProgram(const std::string &name, ShaderProgram &shaderProgram) const override;

	/*!
	* 	\brief			set the position of the pointlight
	* 	\param position	the new position of the pointlight
	*/
	void setPosition(const glm::vec3 &position);

	/*!
	* 	\brief			set the position of the pointlight
	* 	\param position	the new position of the pointlight
	*/
	void setColor(const glm::vec4 &color);

	/*!
	* 	\brief			set the const attenuation factor of the pointlight
	* 	\param position	the new const attenuation factor of the pointlight
	*/
	void setConstAttenuationFactor(float constAttenuationFactor);

	/*!
	* 	\brief			set the linear attenuation factor of the pointlight
	* 	\param position	the new linear attenuation factor of the pointlight
	*/
	void setLinearAttenuationFactor(float linearAttenuationFactor);

	/*!
	* 	\brief			set the quadratic attenuation factor of the pointlight
	* 	\param position	the new quadratic attenuation factor of the pointlight
	*/
	void setQuadraticAttenuationFactor(float quadraticAttenuationFactor);
private:
	//! the position of the pointlight
	glm::vec3 m_position;
	//! the color of the pointlight
	glm::vec4 m_color;
	//! the constant factor for the attenuation
	float m_constantAttenuationFactor;
	//! the linear factor for the attenuation
	float m_linearAttenuationFactor;
	//! the quadratic factor for the attenuation
	float m_quadraticAttenuationFactor;
};
