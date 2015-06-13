#include <Game/GameComponents/World.h>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <Game/GameComponents/Entities/StaticObject.h>
#include <Game/Constants.h>
#include <Game/GameComponents/Entities/Player.h>
#include <iostream>

World::World()
	:m_items(),
	m_size(0),
	m_entities(),
	m_windowSize(0)
{

}

void World::loadMap(const std::string &mapFolder, std::map<std::string, std::shared_ptr<Texture>> tileTextures, std::map<std::string, bool> collidingInfo, std::shared_ptr<Input> input)
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

				if (key.length() > 0)
				{
					glm::vec2 pos = glm::vec2(x, y) * Constants::TILE_SIZE;
					std::shared_ptr<StaticObject> object = std::make_shared<StaticObject>(*this, Constants::TILE_DIMENSION / 2.0f, pos, Constants::TILE_SIZE, tileTextures[key]);
					m_entities.push_back(object);
					m_background.push_back(object);
					m_backgroundColliding.push_back(collidingInfo[key]);
					++x;
				}
			}
			mapSize.x = std::max(mapSize.x, x);
			++mapSize.y;
			++y;
		}
	}
	mapFile.close();

	std::ifstream itemFile;
	itemFile.open(itemPath.str(), std::ios_base::out);
	if (itemFile)
	{
		while (!itemFile.eof())
		{
			std::string line;
			std::getline(itemFile, line);
			std::istringstream iSs(line);
			std::string type;
			iSs >> type;

			if (type == "PLAYER")
			{
				int x;
				int y;
				iSs >> x >> y;
				std::shared_ptr<Entity> player = std::make_shared<Player>(*this, 10.0f, tileToWorld(glm::ivec2(x, y)) + Constants::TILE_SIZE / 2.0f, glm::vec2(5, 5), tileTextures["PLAYER"], input, m_windowSize);
				addPlayer(player);
			}
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

std::shared_ptr<Entity> World::getPlayer()
{
	return m_player;
}

void World::addItem(std::shared_ptr<Entity> e)
{
	m_items.push_back(e);
	m_updateableEntities.push_back(e);
}

void World::update(const GameTime &gameTime)
{
	glm::vec2 playerPos = m_player->getPosition();
	for (std::shared_ptr<Entity> e : m_updateableEntities)
	{
		e->update(gameTime);
	}

	//glm::vec2 offset[8] = { glm::vec2(0, -1), glm::vec2(0, 1), glm::vec2(-1, 0), glm::vec2(1, 0), glm::vec2(-0.5f, -0.5f), glm::vec2(-0.5f, 0.5f), glm::vec2(0.5f, -0.5f), glm::vec2(0.5f, 0.5f) };
	//glm::vec2 newPlayerPos = m_player->getPosition();
	//glm::vec2 movement = newPlayerPos - playerPos;
	//for (int i = 0; i < 8; ++i)
	//{
	//	glm::ivec2 pos = worldToTile(newPlayerPos + offset[i] * Constants::TILE_SIZE / 2.0f);
	//	glm::ivec2 tilePos;
	//	if (pos.x >= 0 && pos.y >= 0 && pos.x < m_size.x && pos.y < m_size.y && m_backgroundColliding[tileToIndex(pos)])
	//	{
	//		std::cout << offset[i].x << "|" << offset[i].y << std::endl;
	//		movement *= (-(glm::abs(offset[i]) - glm::vec2(1)));
	//	}
	//}
	//m_player->setPosition(playerPos + movement)

	glm::vec2 newPlayerPos = m_player->getPosition();
	glm::vec2 movement = newPlayerPos - playerPos;
	glm::vec2 components[2] = { glm::vec2(1, 0), glm::vec2(0, 1) };
	for (int i = 0; i < 2; ++i)
	{
		glm::ivec2 pos = worldToTile(playerPos);
		glm::vec2 tmpPos = playerPos + movement * components[i];
		Rect rPlayer = Rect(tmpPos - Constants::TILE_SIZE / 2.0f, tmpPos + Constants::TILE_SIZE / 2.0f);
		bool collision = false;
		for (int y = -1; y <= 1 && !collision; ++y)
		{
			for (int x = -1; x <= 1 && !collision; ++x)
			{
				if (!(y == 0 && x == 0))
				{
					glm::ivec2 tilePos = pos + glm::ivec2(x, y);
					if (tilePos.x >= 0 && tilePos.y >= 0 && tilePos.x < m_size.x && tilePos.y < m_size.y && m_backgroundColliding[tileToIndex(tilePos)])
					{
						glm::vec2 tileWorldPos = tileToWorld(tilePos);
						Rect rTile = Rect(tileWorldPos, tileWorldPos + Constants::TILE_SIZE);
						collision |= rPlayer.intersects(rTile);
					}
				}
			}
		}
		if (!collision)
		{
			playerPos = tmpPos;
		}
	}
	m_player->setPosition(playerPos);
}

void World::setWindowSize(glm::ivec2 windowSize)
{
	m_windowSize = windowSize;
}

void World::draw()
{
	glm::ivec2 NUMTILES = glm::ivec2(m_windowSize.x / Constants::TILE_SIZE.x + 3, m_windowSize.y / Constants::TILE_SIZE.y + 3);
	glm::vec2 playerPos = m_player->getPosition();
	glm::ivec2 offset = worldToTile(playerPos);

	for (int y = -NUMTILES.y / 2; y < NUMTILES.y / 2; ++y)
	{
		for (int x = -NUMTILES.x / 2; x < NUMTILES.x / 2; ++x)
		{
			glm::ivec2 r(x + offset.x, y + offset.y);
			if (r.x >= 0 && r.y >= 0 && r.x < m_size.x && r.y < m_size.y)
			{
				m_background[tileToIndex(r)]->draw();
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

glm::ivec2 World::worldToTile(glm::vec2 pos)
{
	return glm::ivec2(pos.x / Constants::TILE_SIZE.x, pos.y / Constants::TILE_SIZE.y);
}

glm::vec2 World::tileToWorld(glm::ivec2 pos)
{
	return glm::vec2(pos * Constants::TILE_SIZE_I) ;
}

unsigned int World::tileToIndex(glm::ivec2 pos)
{
	return pos.x + pos.y * m_size.x;
}