#pragma once
#include <glm/glm.hpp>
#include <Game/GameComponents/World.h>
#include <Game/GameComponents/Entities/Entity.h>
#include <Game/GameComponents/Entities/Enemy.h>

class Spawner : public Entity
{
public:
	Spawner(World &world, glm::vec2 position, float spawnRate, std::shared_ptr<Texture> enemyTexture);

	virtual void update(const GameTime& gameTime);

	virtual void draw();
private:
	void spawn();

	float m_spawnRate;

	std::shared_ptr<Texture> m_enemyTexture;
};