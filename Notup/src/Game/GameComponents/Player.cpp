#include <Game/GameComponents/Entities/Player.h>

#include <glm/gtc/constants.hpp>
#define _USE_MATH_DEFINES 
#include <cmath>

Player::Player(World &world, float radius, glm::vec2 position, glm::vec2 size, std::shared_ptr<Texture> texture, std::shared_ptr<Input> input, glm::ivec2 windowSize)
	:Entity(world, radius, position, size),
	m_input(input),
	m_windowSize(windowSize)
{
	m_sprite.initialize();
	m_sprite.setShaderProgram(m_shaderProgram);
	m_sprite.setTexture(texture);
	m_sprite.setDestination(position);
	m_sprite.setOrigin(glm::vec2(m_sprite.getTexture().getWidth() / 2, m_sprite.getTexture().getHeight() / 2), false);
}

void Player::update(const GameTime& gameTime)
{
	const float SQRT1_2 = 0.70710678f;
	const float SPEED = 500.0f;
	float dT = gameTime.getElapsedGameTime() * 0.001f;
	glm::vec2 movement(0.0f);
	if (m_input->keyPressed('w'))
	{
		movement.y -= 1.0f;
	}
	if (m_input->keyPressed('s'))
	{
		movement.y += 1.0f;
	}
	if (m_input->keyPressed('a'))
	{
		movement.x -= 1.0f;
	}
	if (m_input->keyPressed('d'))
	{
		movement.x += 1.0f;
	}

	if (movement.x != 0.0f || movement.y != 0.0f)
	{
		m_pos += glm::normalize(movement) * SPEED * dT;
	}

	glm::vec2 relativeMousePos = m_input->getMousePositionV2() - glm::vec2(m_windowSize)/2.0f;
	m_sprite.setRotation(glm::atan(relativeMousePos.y, relativeMousePos.x) + glm::pi<float>() / 2.0f, false);
	m_sprite.setDestination(m_pos, true);
}