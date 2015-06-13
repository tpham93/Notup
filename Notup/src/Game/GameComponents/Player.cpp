#include <Game/GameComponents/Entities/Player.h>

#include <glm/gtc/constants.hpp>

Player::Player(World &world, float radius, glm::vec2 position, glm::vec2 size, std::shared_ptr<Texture> texture, std::shared_ptr<Input> input, glm::ivec2 windowSize)
	:Entity(world, radius, position, size),
	m_input(input),
	m_windowSize(windowSize)
{
	m_sprite.initialize();
	m_sprite.setShaderProgram(m_shaderProgram);
	m_sprite.setTexture(texture);
	m_sprite.setDestination(position);
}

void Player::update(const GameTime& gameTime)
{
	glm::vec2 relativeMousePos = m_input->getMousePositionV2() - m_windowSize / 2.0f;
	m_sprite.setOrigin(glm::vec2(m_sprite.getTexture().getWidth() / 2, m_sprite.getTexture().getHeight() / 2), false);
	m_sprite.setRotation(glm::atan(relativeMousePos.y, relativeMousePos.x) + glm::pi<float>() / 2.0f, false);
	m_sprite.setDestination(m_windowSize / 2.0f, true);
}