#include <Game/GameComponents/Entities/Player.h>

#include <glm/gtc/constants.hpp>
#include <Game/Constants.h>
#include <Game/GameComponents/World.h>
#include <Game/GameComponents/Entities/LightParticle.h>
#include <Game/GameComponents/Random.h>

Player::Player(World &world, float radius, glm::vec2 position, glm::vec2 size, std::shared_ptr<Texture> texture, std::shared_ptr<Texture> lightTexture, std::shared_ptr<Input> input, glm::ivec2 windowSize)
	:Entity(world, radius, position, size),
	m_input(input),
	m_windowSize(windowSize),
	m_energy(1.0f),
	m_lightTexture(lightTexture)
{
	m_sprite.initialize();
	m_sprite.setShaderProgram(m_shaderProgram);
	m_sprite.setTexture(texture);
	m_sprite.setDestination(position);
	m_sprite.setOrigin(glm::vec2(m_sprite.getTexture().getWidth() / 2, m_sprite.getTexture().getHeight() / 2), false);
}

void Player::update(const GameTime& gameTime)
{
	//const float SQRT1_2 = 0.70710678f;
	float dT = gameTime.getElapsedGameTime() * 0.001f;
	glm::vec2 movement(getMovement());

	if (movement.x != 0.0f || movement.y != 0.0f)
	{
		m_pos += glm::normalize(movement) * Constants::PLAYER_SPEED * dT;
	}

	if (m_input->mouseButtonPressed(MouseButtons::LeftMouseButton))
	{
		flashLight();
	}

	glm::vec2 relativeMousePos = m_input->getMousePositionV2() - glm::vec2(m_windowSize)/2.0f;
	m_sprite.setRotation(glm::atan(relativeMousePos.y, relativeMousePos.x) + glm::pi<float>() / 2.0f, false);
	m_sprite.setDestination(m_pos, true);
}

glm::vec2 Player::getMovement()
{
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

	return movement;
}

void Player::flashLight()
{
	//LightParticle(World &world, glm::vec2 position, glm::vec2 size, std::shared_ptr<Texture> texture, unsigned int lifetime, glm::vec2 direction, float speed);
	if (Random::nextFloat() <= Constants::PLAYER_FLASHLIGHT_RATE)
	{
		for (int i = 0; i < 10; ++i)
		{
			unsigned int lifetime = static_cast<unsigned int>(Constants::LIGHT_TIME * m_energy);
			float speed = Constants::LIGHT_SPEED * m_energy;
			glm::vec2 direction = m_input->getMousePositionV2() - glm::vec2(m_windowSize) / 2.0f;
			float angle = glm::pi<float>() / 8.0f * (Random::nextFloat() - 0.5f);
			float sinAngle = glm::sin<float>(angle);
			float cosAngle = glm::cos<float>(angle);
			glm::vec2 rotatedDirection = glm::normalize(glm::vec2(direction.x * cosAngle + direction.y * -sinAngle, direction.x * sinAngle + direction.y * cosAngle));
			std::shared_ptr<Entity> lightParticle = std::make_shared<LightParticle>(m_world, m_pos + Constants::LIGHT_OFFSET, glm::vec2(16.0f), m_lightTexture, lifetime, rotatedDirection, speed);
			m_world.addLight(lightParticle);
		}
	}
}