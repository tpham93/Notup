#include <Game/GameComponents/Entities/Spawner.h>
#include <Game/GameComponents/Random.h>
#include <Game/Constants.h>

Spawner::Spawner(World &world, glm::vec2 position, float spawnRate, std::shared_ptr<Texture> enemyTexture)
	:Entity(world, 0.0f, position, glm::vec2(0)),
	m_spawnRate(spawnRate),
	m_enemyTexture(enemyTexture)
{
}

void Spawner::update(const GameTime& gameTime)
{
	float r = Random::nextFloat();
	if (r <= m_spawnRate)
	{
		spawn();
	}
}

void Spawner::spawn()
{
	std::shared_ptr<Entity> e = std::make_shared<Enemy>(m_world, 10.0f, m_pos, Constants::TILE_SIZE, m_enemyTexture);
	m_world.addEntity(e);
}

void Spawner::draw()
{
}