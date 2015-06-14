#include <Game/GameComponents/Entities/LightParticle.h>
#include <Game/GameComponents/World.h>
#include <glm/gtc/constants.hpp>

LightParticle::LightParticle(World &world, glm::vec2 position, glm::vec2 size, std::shared_ptr<Texture> texture, unsigned int lifetime, glm::vec2 direction, float speed)
	:Entity(world, 8, position, glm::vec2(16)),
	m_time(lifetime),
	m_direction(direction * speed),
	m_hadCollision(false)
{
	m_sprite.initialize();
	m_sprite.setShaderProgram(m_shaderProgram);
	m_sprite.setTexture(texture);
	m_sprite.setDestination(position, false);
	m_sprite.setOrigin(glm::vec2(m_sprite.getTexture().getWidth() / 2, m_sprite.getTexture().getHeight()), false);
	m_sprite.setRotation(glm::atan(direction.y, direction.x) + glm::pi<float>() / 2.0f);
}

LightParticle::~LightParticle()
{
}

void LightParticle::collision(std::shared_ptr<Entity> e)
{
	m_hadCollision = true;
}

void LightParticle::update(const GameTime& gameTime)
{
	float dT = gameTime.getElapsedGameTime() * 0.001f;
	m_pos += m_direction * dT;
	m_sprite.setDestination(m_pos, true);
	m_time -= gameTime.getElapsedGameTime();
	if (m_time < 0.0f || m_hadCollision)
	{
		m_alive = false;
	}
}

bool LightParticle::drawNormal()
{
	return false;
}