#pragma once

#include<vector>
#include<Framework/Game/GameTime.h>
#include<glm/glm.hpp>

#include<Game/GameComponents/Entities/Entity.h>
#include <map>
#include <Framework/Input/Input.h>

class World
{
public:
	World();

	void loadMap(const std::string &backgroundPath, std::map<std::string, std::shared_ptr<Texture>> tileTextures, std::map<std::string, bool> tileCollidingInformation, std::shared_ptr<Input> input);

	void addPlayer(std::shared_ptr<Entity> e);

	void addEntity(std::shared_ptr<Entity> e);

	void addItem(std::shared_ptr<Entity> e);

	std::shared_ptr<Entity> getPlayer();

	void update(const GameTime& gameTime);

	void draw();

	void setWindowSize(glm::ivec2 windowSize);

	glm::ivec2 worldToTile(glm::vec2 pos);

	glm::vec2 tileToWorld(glm::ivec2 pos);

	unsigned int tileToIndex(glm::ivec2 pos);
private:
	std::shared_ptr<Entity> m_player;
	std::vector<std::shared_ptr<Entity>> m_items;
	std::vector<std::shared_ptr<Entity>> m_entities;
	std::vector<std::shared_ptr<Entity>> m_updateableEntities;
	std::vector<std::shared_ptr<Entity>> m_background;
	std::vector<bool> m_backgroundColliding;
	glm::ivec2 m_size;
	glm::ivec2 m_windowSize;
};