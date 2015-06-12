/**********************************************************************************************
* 										include
**********************************************************************************************/
#include <iostream>
#include <Framework/Shader/GeometryBuffer.h>

/**********************************************************************************************
* 										class definition
**********************************************************************************************/

GeometryBuffer::GeometryBuffer()
	:m_frameBufferId(0),
	m_textures()
{

}

GeometryBuffer::~GeometryBuffer()
{
	if (m_frameBufferId != 0)
	{
		glDeleteFramebuffers(1, &m_frameBufferId);
	}
}

bool GeometryBuffer::init(const glm::ivec2 &windowSize, const glm::ivec2 &framebufferSize, const std::vector<std::string> &names)
{
	m_windowSize = windowSize;
	m_frameBufferSize = framebufferSize;

	m_names = names;
	m_names.emplace_back("depthUnit");
	glGenFramebuffers(1, &m_frameBufferId);
	bind();

	std::vector<GLuint> pixels(framebufferSize.x * framebufferSize.y);
	unsigned int frameBufferNumber = static_cast<unsigned int>(names.size());
	for (unsigned int i = 0; i < frameBufferNumber; ++i)
	{
		Texture& currentTexture = *(m_textures.emplace(names[i], std::make_shared<Texture>()).first->second);
		currentTexture.initialize();
		currentTexture.loadTextureFromPixels(pixels.data(), static_cast<GLuint>(framebufferSize.x), static_cast<GLuint>(framebufferSize.y));
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, currentTexture.getTextureID(), 0);
	}

	Texture& depthtTexture = *(m_textures.emplace("depthUnit", std::make_shared<Texture>()).first->second);
	depthtTexture.initialize();
	depthtTexture.loadTextureFromPixels(pixels.data(), static_cast<GLuint>(framebufferSize.x), static_cast<GLuint>(framebufferSize.y), GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthtTexture.getTextureID(), 0);

	std::vector<GLuint> drawBuffers;
	for (unsigned int i = 0; i < frameBufferNumber; ++i)
	{
		drawBuffers.emplace_back(GL_COLOR_ATTACHMENT0 + i);
	}
	glDrawBuffers(frameBufferNumber, drawBuffers.data());

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cerr << "Framebuffer could not be created!" << std::endl;
		return false;
	}
	
	glBindFramebuffer(GL_FRAMEBUFFER,0);

	return true;
}

void GeometryBuffer::bind(GLenum mode)
{
	glBindFramebuffer(mode, m_frameBufferId);
	glViewport(0, 0, m_frameBufferSize.x, m_frameBufferSize.y);
}

void GeometryBuffer::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, m_windowSize.x, m_windowSize.y);
}

void GeometryBuffer::bindTextures(const std::shared_ptr<ShaderProgram> &shaderProgram)
{
	unbind();
	shaderProgram->use();
	for (unsigned int i = 0; i < m_names.size(); ++i)
	{
		const std::string &textureName = m_names[i];
		const Texture &currentTexture = *m_textures[textureName];

		currentTexture.bind(i);
		shaderProgram->setUniformVariable(textureName, static_cast<GLint>(i));
	}
}