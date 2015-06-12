/**********************************************************************************************
* 										include
**********************************************************************************************/
#include <Framework/UniformStruct/Material/BasicLightingMaterial.h>

/**********************************************************************************************
* 										class definition
**********************************************************************************************/

BasicLightingMaterial::BasicLightingMaterial()
	:m_emission(0),
	m_diffuse(0),
	m_ambient(0),
	m_specular(0),
	m_shininess(0)
{

}

BasicLightingMaterial::~BasicLightingMaterial()
{
}

void BasicLightingMaterial::setEmission(glm::vec4 &emission)
{
	m_emission = emission;
}

void BasicLightingMaterial::setDiffuse(glm::vec4 &diffuse)
{
	m_diffuse = diffuse;
}

void BasicLightingMaterial::setAmbient(glm::vec4 &ambient)
{
	m_ambient = ambient;
}

void BasicLightingMaterial::setSpecular(glm::vec4 &specular)
{
	m_specular = specular;
}

void BasicLightingMaterial::setShininess(float shininess)
{
	m_shininess = shininess;
}

void BasicLightingMaterial::sendToShaderProgram(const std::string &name, ShaderProgram  &shaderProgram) const
{
	// send the texture to the shader program
	TextureMaterial::sendToShaderProgram(name, shaderProgram);
	shaderProgram.setUniformVariable(name + ".emission", m_emission);
	shaderProgram.setUniformVariable(name + ".diffuse", m_diffuse);
	shaderProgram.setUniformVariable(name + ".ambient", m_ambient);
	shaderProgram.setUniformVariable(name + ".specular", m_specular);
	shaderProgram.setUniformVariable(name + ".shininess", m_shininess);
}

