#include <Game/GameComponents/World.h>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <Game/GameComponents/Entities/StaticObject.h>
#include <Game/Constants.h>
#include <Game/GameComponents/Entities/Player.h>
#include <Game/GameComponents/Entities/Enemy.h>
#include <Game/GameComponents/Entities/Spawner.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <Framework/Shader/Shader.h>
#include <set>

const unsigned int World::FRAMEBUFFER_NUM;

World::World(std::shared_ptr<ShaderProgram> textureShader, glm::ivec2 windowSize)
	:m_items(),
	m_size(0),
	m_entities(),
	m_windowSize(windowSize),
	m_textureShader(textureShader),
	m_playerSightField()
{
	std::shared_ptr<MatrixHandler> matrixHandler = m_textureShader->getMatrixHandlerPtr();

	m_lightShader = std::make_shared<ShaderProgram>();
	m_mergeLightShader = std::make_shared<ShaderProgram>();

	std::shared_ptr<Shader> mergeLightfragShader = std::make_shared<Shader>("Shader/MergeLight.frag", GL_FRAGMENT_SHADER);
	std::shared_ptr<Shader> lightfragShader = std::make_shared<Shader>("Shader/Light.frag", GL_FRAGMENT_SHADER);
	std::shared_ptr<Shader> vertexShader = std::make_shared<Shader>("Shader/texture.vert", GL_VERTEX_SHADER);

	mergeLightfragShader->compile();
	lightfragShader->compile();
	vertexShader->compile();

	m_lightShader->create();
	m_lightShader->attachShader(lightfragShader);
	m_lightShader->attachShader(vertexShader);
	m_lightShader->link();
	m_lightShader->setMatrixHandler(matrixHandler);
	m_lightShader->use();
	m_lightShader->updateMatrices();
	m_lightShader->addShaderAttribute(ShaderAttributes(m_lightShader->getAttributeLocation("vertexPos2D"), sizeof(Vertex2DTex), GL_FLOAT, 2, reinterpret_cast<GLvoid*>(offsetof(Vertex2DTex, m_position))));
	m_lightShader->addShaderAttribute(ShaderAttributes(m_lightShader->getAttributeLocation("textureCoord"), sizeof(Vertex2DTex), GL_FLOAT, 2, reinterpret_cast<GLvoid*>(offsetof(Vertex2DTex, m_texCoord))));

	m_mergeLightShader->create();
	m_mergeLightShader->attachShader(mergeLightfragShader);
	m_mergeLightShader->attachShader(vertexShader);
	m_mergeLightShader->link();
	m_mergeLightShader->setMatrixHandler(matrixHandler);
	m_mergeLightShader->use();
	m_mergeLightShader->updateMatrices();
	m_mergeLightShader->addShaderAttribute(ShaderAttributes(m_mergeLightShader->getAttributeLocation("vertexPos2D"), sizeof(Vertex2DTex), GL_FLOAT, 2, reinterpret_cast<GLvoid*>(offsetof(Vertex2DTex, m_position))));
	m_mergeLightShader->addShaderAttribute(ShaderAttributes(m_mergeLightShader->getAttributeLocation("textureCoord"), sizeof(Vertex2DTex), GL_FLOAT, 2, reinterpret_cast<GLvoid*>(offsetof(Vertex2DTex, m_texCoord))));

	std::shared_ptr<ShaderProgram> framebufferShader[FRAMEBUFFER_NUM] = { m_mergeLightShader, m_textureShader };

	//create framebuffer
	m_framebufferSize = m_windowSize;
	GLuint *framebufferData = new GLuint[m_framebufferSize.x * m_framebufferSize.y] {};
	glGenFramebuffers(FRAMEBUFFER_NUM, m_framebufferId);
	for (int i = 0; i < FRAMEBUFFER_NUM; ++i)
	{
		m_framebufferTexture[i] = std::make_shared<Texture>();
		m_framebufferTexture[i]->loadTextureFromPixels(framebufferData, m_framebufferSize.x, m_framebufferSize.y);
		m_framebufferTexture[i]->bind();
		m_framebufferSprite[i].initialize();
		m_framebufferSprite[i].setTexture(m_framebufferTexture[i]);
		m_framebufferSprite[i].setShaderProgram(framebufferShader[i]);
		//m_framebufferSprite[i].setShaderProgram(m_textureShader);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_framebufferId[i]);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_framebufferTexture[i]->getTextureID(), 0);
		m_framebufferSprite[i].setOrigin(glm::vec2(0.0f));
		m_framebufferSprite[i].setDestination(Rect(0, m_windowSize.y, static_cast<float>(m_windowSize.x), -static_cast<float>(m_windowSize.y)));
	}

	delete[] framebufferData;
}
#include<GL/freeglut.h>
void World::loadMap(const std::string &mapFolder, std::map<std::string, std::shared_ptr<Texture>> &tileTextures, std::map<std::string, bool> &collidingInfo, std::shared_ptr<Input> input)
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
					object->setIndex(m_entities.size());
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
				std::shared_ptr<Entity> e = std::make_shared<Player>(*this, 10.0f, tileToWorld(glm::ivec2(x, y)) + Constants::TILE_SIZE / 2.0f, Constants::TILE_SIZE, tileTextures["PLAYER"], tileTextures["LIGHT_PARTICLE"], input, m_windowSize);
				addPlayer(e);
			}
			else if (type == "SPAWNER")
			{
				int x;
				int y;
				float spawnRate;
				iSs >> x >> y >> spawnRate;
				std::shared_ptr<Entity> e = std::make_shared<Spawner>(*this, tileToWorld(glm::ivec2(x, y)) + Constants::TILE_SIZE / 2.0f, spawnRate, tileTextures["ENEMY"]);
				addEntity(e);
			}
			else if (type == "ENEMY")
			{
				int x;
				int y;
				iSs >> x >> y;
				std::shared_ptr<Entity> e = std::make_shared<Enemy>(*this, 10.0f, tileToWorld(glm::ivec2(x, y)) + Constants::TILE_SIZE / 2.0f, Constants::TILE_SIZE, tileTextures["ENEMY"]);
				addEntity(e);
			}
		}
	}
	m_size = mapSize;


	m_playerSightField.initialize();
	m_playerSightField.setTexture(tileTextures["PLAYER_SIGHT_FIELD"]);
	m_playerSightField.setShaderProgram(m_textureShader);
	m_playerSightField.setOrigin(glm::vec2(m_playerSightField.getTexture().getWidth(), m_playerSightField.getTexture().getHeight()) / 2.0f);

}

void World::addPlayer(std::shared_ptr<Entity> e)
{
	m_player = e;
	addEntity(e);
}

void World::addEntity(std::shared_ptr<Entity> e)
{
	e->setIndex(m_entities.size());
	m_updateableEntities.push_back(e);
	m_entities.push_back(e);
}

void World::addLight(std::shared_ptr<Entity> e)
{
	e->setIndex(m_entities.size());
	m_updateableEntities.push_back(e);
	m_light.push_back(e);
	m_entities.push_back(e);
}

std::shared_ptr<Entity> World::getPlayer()
{
	return m_player;
}

void World::addItem(std::shared_ptr<Entity> e)
{
	e->setIndex(m_entities.size());
	m_items.push_back(e);
	m_entities.push_back(e);
}

void World::update(const GameTime &gameTime)
{
	std::vector<glm::vec2> oldPositions;
	for (int i = 0; i < m_updateableEntities.size(); ++i)
	{
		oldPositions.push_back(m_updateableEntities[i]->getPosition());
		m_updateableEntities[i]->update(gameTime);
	}

	for (int i = 0; i < m_items.size(); ++i)
	{
		m_updateableEntities[i]->update(gameTime);
	}

	for (int i = 0; i < m_updateableEntities.size(); ++i)
	{
		std::shared_ptr<Entity> e = m_updateableEntities[i];
		glm::vec2 oldPos = oldPositions[i];
		glm::vec2 newPos = e->getPosition();
		glm::vec2 movement = newPos - oldPos;
		glm::vec2 components[2] = { glm::vec2(1, 0), glm::vec2(0, 1) };
		for (int c = 0; c < 2; ++c)
		{
			glm::ivec2 pos = worldToTile(oldPos);
			glm::vec2 tmpPos = oldPos + movement * components[c];
			glm::vec2 size = e->getSize();
			Rect rEntity = Rect(tmpPos - size / 2.0f, tmpPos + size / 2.0f);
			bool collision = false;
			for (int y = -1; y <= 1 && !collision; ++y)
			{
				for (int x = -1; x <= 1 && !collision; ++x)
				{
					if (!(y == 0 && x == 0))
					{
						glm::ivec2 tilePos = pos + glm::ivec2(x, y);
						unsigned int backgroundIndex = tileToIndex(tilePos);
						if (tilePos.x >= 0 && tilePos.y >= 0 && tilePos.x < m_size.x && tilePos.y < m_size.y && m_backgroundColliding[backgroundIndex])
						{
							glm::vec2 tileWorldPos = tileToWorld(tilePos);
							Rect rTile = Rect(tileWorldPos, tileWorldPos + Constants::TILE_SIZE);
							collision |= rEntity.intersects(rTile);
							if (collision)
							{
								e->collision(m_background[backgroundIndex]);
							}
						}
					}
				}
			}
			if (!collision)
			{
				oldPos = tmpPos;
			}
		}
		e->setPosition(oldPos);
	}

	for (int i = 1; i < m_updateableEntities.size(); ++i)
	{
		std::shared_ptr<Entity> ei = m_updateableEntities[i];
		if (ei->drawNormal())
		{
			glm::vec2 tmpPosI = ei->getPosition();
			glm::vec2 sizeI = ei->getSize();
			Rect rI = Rect(tmpPosI - sizeI / 2.0f, tmpPosI + sizeI / 2.0f);
			for (int j = i+1; j < m_updateableEntities.size(); ++j)
			{
				std::shared_ptr<Entity> ej = m_updateableEntities[j];
				if (!ej->drawNormal())
				{
					glm::vec2 tmpPosJ = ej->getPosition();
					glm::vec2 sizeJ = ej->getSize();
					Rect rJ = Rect(tmpPosJ - sizeJ / 2.0f, tmpPosJ + sizeJ / 2.0f);

					if (rI.intersects(rJ))
					{
						bool eIN = ei->drawNormal();
						bool eJN = ej->drawNormal();
						ei->collision(ej);
						ej->collision(ei);
					}
				}
			}
		}
	}

	deleteDeadEntities();
}

void World::draw()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferId[0]);
	glClear(GL_COLOR_BUFFER_BIT);
	m_textureShader->use();
	glm::mat4 & modelMatrix = m_textureShader->getMatrixHandler().getMatrix("modelMatrix");
	modelMatrix = glm::translate(glm::mat4(), -glm::vec3(m_player->getPosition(), 0) + glm::vec3(m_windowSize, 0) / 2.0f);
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

	for (std::shared_ptr<Entity> e : m_updateableEntities)
	{
		if (e->drawNormal())
		{
			e->draw();
		}
	}

	glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferId[1]);
	glClear(GL_COLOR_BUFFER_BIT);
	m_playerSightField.setDestination(m_player->getPosition(), true);
	m_playerSightField.draw();

	for (std::shared_ptr<Entity> e : m_light)
	{
		e->draw();
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	modelMatrix = glm::mat4(1.0f);
	m_framebufferTexture[1]->bind(1);
	m_framebufferSprite[0].draw();
}

//Gerd was here 13.06. um 16:35

glm::ivec2 World::worldToTile(glm::vec2 pos)
{
	return glm::ivec2(pos.x / Constants::TILE_SIZE.x, pos.y / Constants::TILE_SIZE.y);
}

glm::vec2 World::tileToWorld(glm::ivec2 pos)
{
	return glm::vec2(pos * Constants::TILE_SIZE_I);
}

unsigned int World::tileToIndex(glm::ivec2 pos)
{
	return pos.x + pos.y * m_size.x;
}

void World::deleteDeadEntities()
{
	deleteDeadEntities(m_entities);
	deleteDeadEntities(m_light);
	deleteDeadEntities(m_items);
	deleteDeadEntities(m_updateableEntities);
}
void World::deleteDeadEntities(std::vector<std::shared_ptr<Entity>> &entities)
{
	for (int i = entities.size() - 1; i >= 0; --i)
	{
		if (!entities[i]->isAlive())
		{
			entities.erase(entities.begin() + i);
		}
	}
}