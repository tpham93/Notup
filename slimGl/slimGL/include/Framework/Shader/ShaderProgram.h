#pragma once

/********************************************************************************************** 
* 										includes
**********************************************************************************************/
#include <memory>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <Framework/Shader/ShaderAttributes.h>
#include <Framework/Shader/MatrixHandler.h>
#include <Framework/Game/GameTime.h>

/********************************************************************************************** 
* 										forward declarations
**********************************************************************************************/
class Shader;
class UniformStruct;

/********************************************************************************************** 
* 										class declaration
**********************************************************************************************/

/*!
* 	\brief	a class wrapping up glsl shader
*/
class ShaderProgram
{
public:
	/*!
	* 	\brief	copies are not allowed!
	*/
	ShaderProgram(const ShaderProgram &shaderProgram) = delete;

	/*!
	* 	\brief	assignments aren't allowed!
	*/
	ShaderProgram &operator=(const ShaderProgram &shaderProgram) = delete;

	/*!
	* 	\brief			standard constructor
	*/
	ShaderProgram();

	/*!
	* 	\brief			destructor
	*/
	virtual ~ShaderProgram();

	/*!
	* 	\brief			creating the program on the gpu
	* 	\pre			no active program in this instance
	* 	\post			shader program created on the gpu
	*/
	void create();

	/*!
	* 	\brief			attach the added shader to the program
	* 	\param shader	the shader you want to attach to the program
	* 	\return			true if everything went succesfully
	* 	\pre			the shader is already compiled
	* 	\post			the shader is attached to the gpu
	*/
	bool attachShader(std::shared_ptr<const Shader> shader);


	/*!
	* 	\brief			linking the attached shaders
	* 	\pre			a created program on the gpu with attached shader
	* 					the attached shader have to be all valid
	* 	\post			the shader are linked together
	*/
	void link();


	/*!
	* 	\brief			deleting the program from the gpu
	* 	\pre			created a shader program on the gpu
	* 	\post			shader program deleted from the gpu
	*/
	void free();


	/*!
	* 	\brief			using the program as part of the rendering pipeline
	* 	\pre			linked shader program
	* 	\post			the program is part of the rendering pipeline
	*/
	void use() const;


	/*!
	* 	\brief				pushing a matrix from the matrix handler to the gpu
	*	\param matrixName	the name of the matrix, which should be updated
	* 	\pre				matrix handler set and shader program is used
	* 	\post				the matrices are pushed to the gpu
	*/
	void updateMatrix(std::string matrixName);


	/*!
	* 	\brief			pushing all matrices from the matrix handler to the gpu
	* 	\pre			matrix handler set and shader program is used
	* 	\post			the matrices are pushed to the gpu
	*/
	void updateMatrices();


	/*!
	* 	\brief			enable the pointer for the attributes
	* 	\pre			none
	* 	\post			pointer to the attributes can be used to set the vertex data
	*/
	virtual void enableAttribPointer() const;


	/*!
	* 	\brief				adds an attribute, so the pointer to it can be enabled with enableAttribPointer
	* 	\param attribute	the attribute which should be added
	* 	\pre				none
	* 	\post				the pointer to it can be enabled with enableAttribPointer
	*/
	void addShaderAttribute(const ShaderAttributes &attribute);


	/*!
	* 	\brief			set all pointer to the attribute in the shader program
	* 	\pre			none
	* 	\post			the pointer are set
	*/
	virtual void setAttributePointer();


	/*!
	* 	\brief			set the pointer to the i-th attribute in the shader program
	* 	\param i		the index for the attribute
	* 	\pre			none
	* 	\post			the i-th pointer is set
	*/
	virtual void setAttributePointer(int i);


	/*!
	* 	\brief			setting a uniform variable
	* 	\param name		the name of the variable you want to set
	* 	\param value	the new value of the variable
	* 	\pre			the program has to be linked, and bound
	* 					the type of the value has to match the value of the variable in the shader
	* 	\post			the value of the variable is set to the new value
	*/
	void setUniformVariable(std::string name, GLint value);


	/*!
	* 	/overload void setUniformVariable(std::string name, GLuint value)
	*/
	void setUniformVariable(std::string name, GLuint value);


	/*!
	* 	/overload void setUniformVariable(std::string name, GLfloat value)
	*/
	void setUniformVariable(std::string name, GLfloat value);


	/*!
	* 	/overload void setUniformVariable(std::string name, glm::vec2 value)
	*/
	void setUniformVariable(std::string name, const glm::vec2  &value);


	/*!
	* 	/overload void setUniformVariable(std::string name, glm::vec3 value)
	*/
	void setUniformVariable(std::string name, const glm::vec3  &value);


	/*!
	* 	/overload void setUniformVariable(std::string name, glm::vec4 value)
	*/
	void setUniformVariable(std::string name, const glm::vec4  &value);


	/*!
	* 	/overload void setUniformVariable(std::string name, glm::mat4 value)
	*/
	void setUniformVariable(std::string name, const glm::mat4  &value);


	/*!
	* 	/overload void setUniformVariable(std::string name, glm::mat4 value)
	*/
	void setUniformVariable(std::string name, const UniformStruct &uniformStruct);


	/*!
	* 	\brief			get the location of a uniform variable of a shader
	* 	\param	name	the name of the variable you want the location from
	* 	\return			the location of the variable, 0 if there was none, otherwise the location of the uniform variable
	* 	\pre			the program has to be bound
	* 	\post			none
	*/
	GLint getVariableLocation(std::string name) const;


	/*!
	* 	\brief			get the location of a attribute of a shader
	* 	\param	name	the name of the attribute you want the location from
	* 	\return			the location of the variable, 0 if there was none, otherwise the location of the attribute
	* 	\pre			the program has to be bound
	* 	\post			none
	*/
	GLint getAttributeLocation(std::string name) const;


	/*!
	* 	\brief					set the new matrix handler
	* 	\param matrixHandler	the new matrix handler
	*/
	void setMatrixHandler(std::shared_ptr<MatrixHandler> matrixHandler);


	/*!
	* 	\brief		get the currently used matrix handler
	* 	\return		the used matrix handler
	*/
	MatrixHandler &getMatrixHandler();


	/*!
	* 	\brief		get the currently used matrix handler
	* 	\return		the used matrix handler
	*/
	const MatrixHandler &getMatrixHandler() const;


	/*!
	* 	\brief		get the program which is currently used
	* 	\return		0 if there is none used, otherwise the program id is returned
	*/
	static GLint getCurrentUsedProgram();

private:

	//! bound shader
	static GLint currentUsedShader;


	//! the id of the shader on the gpu
	GLint m_programId;


	//! the sources for the shader
	std::vector<std::shared_ptr<const Shader>> m_attachedShader;


	//! the attributes of the shader
	std::vector<const ShaderAttributes> m_attributes;


	//! the handler for the matrices
	std::shared_ptr<MatrixHandler> m_matrixHandler;

};
