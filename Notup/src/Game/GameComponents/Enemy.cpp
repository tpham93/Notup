#include <Game/GameComponents/Entities/Enemy.h>

#include <glm/gtc/constants.hpp>
#include <Game/GameComponents/World.h>
#include <Game/Constants.h>
#include <glm/gtx/norm.hpp>
#include <limits>
#include <random>
#include <algorithm>
#include <Game/GameComponents/Random.h>

Enemy::Enemy(World &world, float radius, glm::vec2 position, glm::vec2 size, std::shared_ptr<Texture> texture)
	:Entity(world, radius, position, size),
	m_target(nullptr),
	m_targetPosition(),
	m_direction(),
	m_time(0.0f),
	m_targetCooldown(0.0f),
	m_hp(100.0f)
{
	m_sprite.initialize();
	m_sprite.setShaderProgram(m_shaderProgram);
	m_sprite.setTexture(texture);
	m_sprite.setDestination(position);
	m_sprite.setOrigin(glm::vec2(m_sprite.getTexture().getWidth() / 2, m_sprite.getTexture().getHeight() / 2), false);
}

void Enemy::update(const GameTime& gameTime)
{

	float dT = gameTime.getElapsedGameTime() * 0.001f;
	m_time -= gameTime.getElapsedGameTime();
	m_targetCooldown = std::max(m_targetCooldown - gameTime.getElapsedGameTime(), 0.0f);

	std::vector<std::shared_ptr<Entity>> possibleTargets;
	possibleTargets.emplace_back(m_world.getPlayer());
	float minDist = std::numeric_limits<float>::infinity();
	int targetIndex = -1;

	if (m_targetCooldown == 0.0f)
	{
		for (int i = 0; i < possibleTargets.size(); ++i)
		{
			if (inHearRadius(possibleTargets[i]))
			{
				float dist = glm::length2(m_targetPosition - m_pos);
				if (dist < minDist)
				{
					targetIndex = i;
				}
			}
		}
		if (targetIndex > -1)
		{
			m_direction = glm::normalize(m_targetPosition - m_pos);
			m_time = Constants::ENEMY_RANDOM_TIME * Random::nextFloat()+Constants::ENEMY_CONST_TIME;
			m_target = possibleTargets[targetIndex];
			m_targetPosition = m_target->getPosition();
		}
		else
		{
			m_target = nullptr;
		}
	}

	if (m_target == nullptr && (m_targetPosition == glm::vec2(0.0f) || m_time < 0.0f))
	{
		m_direction = glm::vec2(Random::nextFloat(), Random::nextFloat()) * 2.0f - glm::vec2(1.0f);
		m_time = Constants::ENEMY_RANDOM_TIME * Random::nextFloat()+Constants::ENEMY_CONST_TIME;
		m_targetPosition = m_pos + m_time * m_direction * Constants::ENEMY_SPEED;
	}
	m_pos += m_direction * dT * Constants::ENEMY_SPEED;

	m_sprite.setRotation(glm::atan(m_direction.y, m_direction.x) + glm::pi<float>() / 2.0f, false);
	m_sprite.setDestination(m_pos, true);
}

bool Enemy::inHearRadius(std::shared_ptr<Entity> e)
{
	return glm::length2(e->getPosition() - m_pos) <= Constants::HEAR_RADIUS_ENEMY_SQ;
}

void Enemy::collision(std::shared_ptr<Entity> e)
{
	if (e->drawNormal())
	{
		m_targetPosition = glm::vec2(0.0f);
		m_time = 0.0f;
		if (m_target != nullptr)
		{
			m_target = nullptr;
			m_targetCooldown = Constants::ENEMY_TARGET_COOLDOWN_CONST + (Random::nextFloat()* Constants::ENEMY_TARGET_COOLDOWN);
		}
	}
	else
	{
		m_hp -= 0.1f;
		if (m_hp < 0.0f)
		{
			m_alive = false;
		}
	}
}