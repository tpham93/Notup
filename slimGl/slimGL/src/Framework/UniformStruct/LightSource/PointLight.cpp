/**********************************************************************************************
* 										include
**********************************************************************************************/
#include <Framework/UniformStruct/LightSource/PointLight.h>

/**********************************************************************************************
* 										class definition
**********************************************************************************************/

PointLight::PointLight()
{

}

PointLight::~PointLight()
{

}
void PointLight::sendToShaderProgram(const std::string &name, ShaderProgram &shaderProgram) const
{
	shaderProgram.setUniformVariable(name + ".position", m_position);
	shaderProgram.setUniformVariable(name + ".color", m_color);
	shaderProgram.setUniformVariable(name + ".constantAttenuationFactor", m_constantAttenuationFactor);
	shaderProgram.setUniformVariable(name + ".linearAttenuationFactor", m_linearAttenuationFactor);
	shaderProgram.setUniformVariable(name + ".quadraticAttenuationFactor", m_quadraticAttenuationFactor);
}

void PointLight::setPosition(const glm::vec3 &position)
{
	m_position = position;
}

void PointLight::setColor(const glm::vec4 &color)
{
	m_color = color;
}

void PointLight::setConstAttenuationFactor(float constAttenuationFactor)
{
	m_constantAttenuationFactor = constAttenuationFactor;
}

void PointLight::setLinearAttenuationFactor(float linearAttenuationFactor)
{
	m_linearAttenuationFactor = linearAttenuationFactor;
}

void PointLight::setQuadraticAttenuationFactor(float quadraticAttenuationFactor)
{
	m_quadraticAttenuationFactor = quadraticAttenuationFactor;
}