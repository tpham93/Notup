#include <Game/GameComponents/World.h>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <Game/GameComponents/Entities/StaticObject.h>
#include <Game/Constants.h>

World::World()
	:m_backGround(),
	m_items(),
	m_size(0),
	m_entities(),
	m_windowSize(0)
{

}

void World::loadMap(const std::string &mapFolder, std::map<std::string, std::shared_ptr<Texture>> tileTextures)
{
	std::ostringstream itemPath;
	itemPath << mapFolder << "items.txt";
	std::ostringstream mapPath;
	mapPath << mapFolder << "map.txt";

	glm::ivec2 mapSize(0, 0);

	std::ifstream mapFile;
	mapFile.open(mapPath.str(), std::ios_base::out);
	if (mapFile)
	{
		int x = 0;
		int y = 0;
		while (!mapFile.eof())
		{
			std::string line;
			std::getline(mapFile, line);
			std::istringstream lineSs(line);
			x = 0;
			while (!lineSs.eof())
			{
				std::string key;
				lineSs >> key;

				glm::vec2 pos = glm::vec2(x, y) * Constants::TILE_SIZE;
				std::shared_ptr<StaticObject> object = std::make_shared<StaticObject>(*this, Constants::TILE_DIMENSION / 2.0f, pos, Constants::TILE_SIZE, tileTextures[key]);
				m_entities.push_back(object);
				m_background.push_back(object);
				++x;
			}
			mapSize.x = std::max(mapSize.x, x);
			++mapSize.y;
			++y;
		}
	}
	m_size = mapSize;
}

void World::addPlayer(std::shared_ptr<Entity> e)
{
	m_player = e;
	addEntity(e);
}

void World::addEntity(std::shared_ptr<Entity> e)
{
	m_entities.push_back(e);
	m_updateableEntities.push_back(e);
}

void World::addItem(std::shared_ptr<Entity> e)
{
	m_items.push_back(e);
	m_updateableEntities.push_back(e);
}

void World::update(const GameTime &gameTime)
{
	for (std::shared_ptr<Entity> e : m_updateableEntities)
	{
		e->update(gameTime);
	}
}

void World::setWindowSize(glm::ivec2 windowSize)
{
	m_windowSize = windowSize;
}

void World::draw()
{
	glm::ivec2 NUMTILES = glm::ivec2(m_windowSize.x / Constants::TILE_SIZE.x + 3, m_windowSize.y / Constants::TILE_SIZE.y + 3);
	glm::vec2 playerPos = m_player->getPosition();
	glm::ivec2 offset = glm::ivec2(std::ceil(playerPos.x / Constants::TILE_SIZE.x), std::ceil(playerPos.y / Constants::TILE_SIZE.y));

	for (int y = -NUMTILES.y / 2; y < NUMTILES.y / 2; ++y)
	{
		for (int x = -NUMTILES.x / 2; x < NUMTILES.x / 2; ++x)
		{
			int rx = (x + offset.x);
			int ry = (y + offset.y);
			if (rx >= 0 && ry >= 0 && rx < m_size.x && ry < m_size.y)
			{
				unsigned int index = rx + ry * m_size.x;
				m_background[index]->draw();
			}
		}
	}

	for (std::shared_ptr<Entity> e : m_items)
	{
		e->draw();
	}

	m_player->draw();
}

//Gerd was here 13.06. um 16:35