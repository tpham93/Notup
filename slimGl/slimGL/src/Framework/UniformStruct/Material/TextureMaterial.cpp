/**********************************************************************************************
* 										include
**********************************************************************************************/
#include <Framework/UniformStruct/Material/TextureMaterial.h>

/**********************************************************************************************
* 										class definition
**********************************************************************************************/

TextureMaterial::TextureMaterial()
	:m_texture(nullptr),
	m_textureUnit(0)
{

}

TextureMaterial::~TextureMaterial()
{
}

void TextureMaterial::bindRessources(const std::string &name, ShaderProgram &shaderProgram) const
{
	m_texture->bind(m_textureUnit);
}

void TextureMaterial::sendToShaderProgram(const std::string &name, ShaderProgram &shaderProgram) const
{
	shaderProgram.setUniformVariable(name + ".textureUnit", static_cast<GLint>(m_textureUnit));
}

void TextureMaterial::setTexture(std::shared_ptr<Texture> texture)
{
	m_texture = texture;
}