/**********************************************************************************************
* 										includes
**********************************************************************************************/
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <Framework/Shader/ShaderProgram.h>
#include <Framework/Shader/Shader.h>
#include <Framework/UniformStruct/UniformStruct.h>




/**********************************************************************************************
* 										static variable definition
**********************************************************************************************/

GLint ShaderProgram::currentUsedShader = 0;

/**********************************************************************************************
* 										class definition
**********************************************************************************************/

ShaderProgram::ShaderProgram()
	:m_programId(0),
	m_attachedShader(),
	m_attributes(),
	m_matrixHandler(nullptr)
{

}

ShaderProgram::~ShaderProgram()
{
	if (m_programId != 0)
	{
		free();
	}
}

void ShaderProgram::create()
{
	// creating the program on the cpu
	m_programId = glCreateProgram();
}


bool ShaderProgram::attachShader(std::shared_ptr<const Shader> shader)
{
	// attach the compiled shader to the program
	glAttachShader(m_programId, shader->getShaderId());
	m_attachedShader.push_back(shader);

	return true;
}

void ShaderProgram::link()
{
	assert(m_programId != 0 && "there is nothing to link!");
	glLinkProgram(m_programId);

	GLint programSuccess;
	// check for errors
	glGetProgramiv(m_programId, GL_LINK_STATUS, &programSuccess);
	if (programSuccess != GL_TRUE)
	{
		// error occured
		std::cerr << "couldn't link the program " << m_programId << std::endl;

		// printing the program log
		// check if the id is really of a program
		if (glIsProgram(m_programId))
		{
			// initialize variables for the space
			int infoLogLength = 0;
			int maxLogLength = 0;

			// getting the length of the log
			glGetProgramiv(m_programId, GL_INFO_LOG_LENGTH, &maxLogLength);

			// allocate the string 
			char  *infoLog = new char[maxLogLength];

			// get the info log
			glGetProgramInfoLog(m_programId, maxLogLength, &infoLogLength, infoLog);

			// print the log if there is any
			if (infoLogLength > 0)
			{
				std::cerr << infoLog << std::endl;
			}

			// free the memory allocated to save the log
			delete[] infoLog;
		}
		else
		{
			std::cerr << "the id " << m_programId << " is not of a program" << std::endl;
		}
	}

	// detach all attached shader
	for (unsigned int i = 0; i < m_attachedShader.size(); ++i)
	{
		//detach attached shader
		glDetachShader(m_programId, m_attachedShader[i]->getShaderId());
	}
}

void ShaderProgram::free()
{
	assert(m_programId != 0 && "there is nothing to free!");

	// deleting the program from the gpu
	glDeleteProgram(m_programId);
}

void ShaderProgram::use() const
{
	if (currentUsedShader != m_programId)
	{
		glUseProgram(m_programId);
	}
}

void ShaderProgram::updateMatrix(std::string matrixName)
{
	assert(m_matrixHandler != nullptr   &&"matrix handler has to be set!");
	setUniformVariable(matrixName, m_matrixHandler->getMatrix(matrixName));
}
#include <Framework/Helper/Helper.h>
void ShaderProgram::updateMatrices()
{
	assert(m_matrixHandler != nullptr   &&"matrix handler has to be set!");
	std::map<std::string, std::stack<glm::mat4>> &matrices = m_matrixHandler->getMatrices();
	for (const std::pair<std::string, std::stack<glm::mat4>> &pair : matrices)
	{

		setUniformVariable(pair.first, pair.second.top());
		Helper::checkGlForError(std::cerr, pair.first);
	}
}


void ShaderProgram::enableAttribPointer() const
{
	// iterate through all attributes and enable them
	for (unsigned int i = 0; i < m_attributes.size(); ++i)
	{
		// enable the i-th attribute
		glEnableVertexAttribArray(m_attributes[i].getAttributeLocation());
	}
}

void ShaderProgram::addShaderAttribute(const ShaderAttributes &attribute)
{
	m_attributes.push_back(attribute);
}

void ShaderProgram::setAttributePointer()
{
	// iterate through all attributes and reset them
	for (unsigned int i = 0; i < m_attributes.size(); ++i)
	{
		ShaderAttributes &currentAttribute = m_attributes[i];
		// enable the i-th attribute
		glVertexAttribPointer(currentAttribute.getAttributeLocation(), currentAttribute.getSize(), currentAttribute.getType(), GL_FALSE, currentAttribute.getStride(), currentAttribute.getDataptr());
	}
} 

void ShaderProgram::setAttributePointer(int i)
{
	// check if the index is too high
	assert(static_cast<unsigned int>(i) < m_attributes.size() && "the index is too high!");
	// enable the i-th attribute
	glVertexAttribPointer(m_attributes[i].getAttributeLocation(), 2, GL_FLOAT, GL_FALSE, m_attributes[i].getStride(), m_attributes[i].getDataptr());
}

void ShaderProgram::setUniformVariable(std::string name, GLint value)
{
	GLint variableLocation = getVariableLocation(name); use();
	glUniform1iv(variableLocation, 1, &value);
}
void ShaderProgram::setUniformVariable(std::string name, GLuint value)
{
	GLint variableLocation = getVariableLocation(name); use();
	glUniform1uiv(variableLocation, 1, &value);
}
void ShaderProgram::setUniformVariable(std::string name, GLfloat value)
{
	GLint variableLocation = getVariableLocation(name); use();
	glUniform1fv(variableLocation, 1, &value);
}
void ShaderProgram::setUniformVariable(std::string name, const glm::vec2  &value)
{
	GLint variableLocation = getVariableLocation(name); use();
	glUniform2fv(variableLocation, 1, glm::value_ptr(value));
}
void ShaderProgram::setUniformVariable(std::string name, const glm::vec3 &value)
{
	GLint variableLocation = getVariableLocation(name); use();
	glUniform3fv(variableLocation, 1, glm::value_ptr(value));
}
void ShaderProgram::setUniformVariable(std::string name, const  glm::vec4  &value)
{
	GLint variableLocation = getVariableLocation(name); use();
	glUniform4fv(variableLocation, 1, glm::value_ptr(value));
}
void ShaderProgram::setUniformVariable(std::string name, const glm::mat4  &value)
{
	GLint variableLocation = getVariableLocation(name); use();
	glUniformMatrix4fv(variableLocation, 1, GL_FALSE, glm::value_ptr(value));
}
void ShaderProgram::setUniformVariable(std::string name, const UniformStruct &value)
{
	value.sendToShaderProgram(name, *this);
}

GLint ShaderProgram::getVariableLocation(std::string name) const
{
	// get the variale location
	GLint location = glGetUniformLocation(m_programId, name.c_str());

	// check if the location is not valid
	if (location == -1)
	{
		assert(std::cerr << "uniform variable " << name << " was not found" << std::endl);
	}

	return location;
}

GLint ShaderProgram::getAttributeLocation(std::string name) const
{

	// get the variale location
	GLint location = glGetAttribLocation(m_programId, name.c_str());

	// check if the location is not valid
	if (location == -1)
	{
		assert(std::cerr << "attribute " << name << " was not found" << std::endl);
	}

	return location;
}

void ShaderProgram::setMatrixHandler(std::shared_ptr<MatrixHandler> matrixHandler)
{
	m_matrixHandler = matrixHandler;
}

MatrixHandler &ShaderProgram::getMatrixHandler()
{
	return*m_matrixHandler;
}

std::shared_ptr<MatrixHandler> ShaderProgram::getMatrixHandlerPtr()
{
	return m_matrixHandler;
}

const MatrixHandler &ShaderProgram::getMatrixHandler() const
{
	return*m_matrixHandler;
}

GLint ShaderProgram::getCurrentUsedProgram()
{
	return currentUsedShader;
}