#pragma once

#include <Game/GameComponents/Entities/Entity.h>


class Enemy : public Entity
{
public:
	Enemy(World &world, float radius, glm::vec2 position, glm::vec2 size, std::shared_ptr<Texture> texture);

	virtual void update(const GameTime& gameTime);

	//virtual void draw();

	virtual void collision(std::shared_ptr<Entity> e);
private:
	bool inHearRadius(std::shared_ptr<Entity> e);
	std::shared_ptr<Entity> m_target;
	glm::vec2 m_targetPosition;
	glm::vec2 m_direction;
	float m_time;
	float m_targetCooldown;
	float m_hp;
};