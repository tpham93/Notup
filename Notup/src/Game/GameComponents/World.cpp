#include <Game/GameComponents/World.h>

World::World(std::string background, std::string items)
	:m_backGround(),
	m_items(),
	m_size(0),
	m_entities()
{
	
}

World::World(std::vector<unsigned int> &background, std::vector<Entity> &items)
	:m_backGround(),
	m_items(),
	m_size(0),
	m_entities()
{

}

void World::addEntity(std::shared_ptr<Entity> e)
{
	m_entities.push_back(e);
}

void World::addItem(std::shared_ptr<Entity> e)
{
	m_items.push_back(e);
}

void World::update(GameTime &gameTime)
{
	for (std::shared_ptr<Entity> e : m_entities)
	{
		e->update(gameTime);
	}
}

void World::draw()
{
	for (std::shared_ptr<Entity> e : m_entities)
	{
		e->draw();
	}
}