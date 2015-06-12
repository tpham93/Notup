/********************************************************************************************** 
* 										includes
**********************************************************************************************/
#include <assert.h>
#include <iostream>
#include <fstream>
#include <Framework/Shader/Shader.h>

/********************************************************************************************** 
* 										class definition
**********************************************************************************************/
Shader::Shader(std::string filepath, GLenum shaderType)
	:m_filepath(filepath),
	m_shaderType(shaderType),
	m_shaderId(0)
{
	// check if the shadertype is valid
	assert((shaderType == GL_VERTEX_SHADER || shaderType == GL_TESS_CONTROL_SHADER || shaderType == GL_TESS_EVALUATION_SHADER || shaderType == GL_GEOMETRY_SHADER || shaderType == GL_FRAGMENT_SHADER || shaderType == GL_COMPUTE_SHADER)  &&"shaderType  is invalid! valid values are: GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_GEOMETRY_SHADER, GL_FRAGMENT_SHADER and GL_COMPUTE_SHADER");
}

Shader::~Shader()
{
	if (m_shaderId != 0)
	{
		free();
	}

}

void Shader::free()
{
	glDeleteShader(m_shaderId);
	m_shaderId = 0;
}

bool Shader::compile()
{
	// create a shader on the gpu
	m_shaderId = glCreateShader(m_shaderType);
	// open the source file and get the source code
	std::string sourcecode;
	// open the source file
	std::ifstream fileStream(m_filepath);
	// check if it was succesful
	if (!fileStream)
	{
		std::cerr << "couldnt load the file: " << m_filepath << std::endl;
		return false;
	}
	// copy the source code to the string
	sourcecode.assign(std::istreambuf_iterator<char>(fileStream), std::istreambuf_iterator<char>());
	// close the opened stream
	fileStream.close();
	// send the source code to the gpu
	const char*  sourcecode_c = sourcecode.c_str();
	GLint sourcecodeLength = static_cast<GLint>(sourcecode.length());
	glShaderSource(m_shaderId, 1, &sourcecode_c, NULL);
	// compile the source
	glCompileShader(m_shaderId);
	GLint success = 0;
	// check if compilation was succesful
	glGetShaderiv(m_shaderId, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		// get the length of the log
		GLint logLength = 0;
		glGetShaderiv(m_shaderId, GL_INFO_LOG_LENGTH, &logLength);
		// get the log
		GLchar* log = new GLchar[logLength];
		glGetShaderInfoLog(m_shaderId, logLength, &logLength, log);
		// print error message
		std::cerr << "couldnt compile the shader: " << m_filepath << std::endl;
		std::cerr << "Log: " << std::endl;
		std::cerr << log << std::endl;
		return false;
	}

	return true;
}

std::string Shader::getFilepath() const
{
	return m_filepath;
}

GLenum Shader::getShaderType() const
{
	return m_shaderType;
}

GLint Shader::getShaderId() const
{
	return m_shaderId;
}