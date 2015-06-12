#pragma once

/**********************************************************************************************
* 										includes
**********************************************************************************************/
#include <Framework/Resources/Texture.h>
#include <Framework/Shader/ShaderProgram.h>
#include <Framework/UniformStruct/Material/Material.h>

/**********************************************************************************************
* 										class declaration
**********************************************************************************************/

/*!
* 	\brief	a very basic material with just a texture
*/
class TextureMaterial : public Material
{
public:
	/*!
	* 	\brief	constructor
	*/
	TextureMaterial();

	/*!
	* 	\brief	destructor
	*/
	virtual ~TextureMaterial();


	/*!
	* 	\brief					binding the ressources used for the material to the shader program
	* 								uses sendToShadrProgram(ShaderProgram &shaderProgram) const
	* 	\param shaderProgram	the shader program where the material should be bound to
	*/
	virtual void bindRessources(const std::string &name, ShaderProgram &shaderProgram) const;

	/*!
	* 	\brief					binds the material to the shader program
	* 	\param shaderProgram	the shader program where the material should be bound to
	* 	\pre					the shader program is compiled and linked
	* 	\post					the shader program uses the material in the next draw calls
	*/
	virtual void sendToShaderProgram(const std::string &name, ShaderProgram &shaderProgram) const override;

	/*!
	* 	\brief			binds the material to the shader program
	* 	\param texture	the texture the material should use
	*/
	void setTexture(std::shared_ptr<Texture> texture);

	/*!
	* 	\brief				set the texture unit
	* 	\param textureUnit	the texture unit used by the material
	*/
	void setTexture(GLuint textureUnit);
private:
	//! the texture id of the texture
	std::shared_ptr<Texture> m_texture;
	//! the textureunit used
	GLuint m_textureUnit;
};
