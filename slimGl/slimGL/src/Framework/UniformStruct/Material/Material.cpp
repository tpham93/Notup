/********************************************************************************************** 
* 										includes
**********************************************************************************************/
#include <Framework/UniformStruct/Material/Material.h>

/********************************************************************************************** 
* 										class definition
**********************************************************************************************/

unsigned int Material::lastAssignedMaterialId = 0;
unsigned int Material::currentBoundMaterialId = 0;

Material::Material()
	:m_materialId(++lastAssignedMaterialId)
{
}

Material::~Material()
{
	if (currentBoundMaterialId == m_materialId)
	{
		currentBoundMaterialId = 0;
	}
}

void Material::bind(const std::string &name, ShaderProgram &shaderProgram) const
{
	bindRessources(name, shaderProgram);
	if (currentBoundMaterialId != m_materialId)
	{
		sendToShaderProgram(name, shaderProgram);
		currentBoundMaterialId = m_materialId;
	}
}

void Material::bindRessources(const std::string &name, ShaderProgram &shaderProgram) const
{
}
