#pragma once

/**********************************************************************************************
* 										includes
**********************************************************************************************/
#include <glm/glm.hpp>
#include <memory>
#include <map>
#include <Framework/Resources/Texture.h>
#include <Framework/Shader/ShaderProgram.h>

/**********************************************************************************************
* 										class declaration
**********************************************************************************************/
class GeometryBuffer
{
public:
	/*!
	* 	\brief standard constructor
	*/
	GeometryBuffer();

	/*!
	* 	\brief desturctor
	*/
	~GeometryBuffer();

	/*!
	*	\brief						initializing the geometry buffer
	*	\param frameBuffer			the size of the framebuffer
	*	\param windowSize			the size of the window
	*	\param names				the names of the shader uniform variables for the textures(excluding the depth buffer)
	*	\return						true if the frame buffer was build succesfully
	*/
	bool init(const glm::ivec2 &windowSize, const glm::ivec2 &frameBufferSize, const std::vector<std::string> &names);

	/*!
	*	\brief			binding the geometry buffer to read or write from it
	*	\param mode		the mode for the geometry buffer, which can be either GL_DRAW_FRAMEBUFFER or GL_DRAW_FRAMEBUFFER
	*/
	void bind(GLenum mode = GL_FRAMEBUFFER);

	/*!
	*	\brief			unbind the framebuffer
	*/
	void unbind();

	/*!
	*	\brief			binding the textures
	*/
	void bindTextures(const std::shared_ptr<ShaderProgram> &shaderProgram);

//private:
	GLuint m_frameBufferId;
	std::map<std::string, std::shared_ptr<Texture>> m_textures;
	std::vector<std::string> m_names;
	glm::ivec2 m_windowSize;
	glm::ivec2 m_frameBufferSize;
};