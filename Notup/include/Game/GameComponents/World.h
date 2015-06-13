#pragma once

#include<vector>
#include<Framework/Game/GameTime.h>
#include<glm/glm.hpp>

#include<Game/GameComponents/Entities/Entity.h>
#include <map>

class World
{
public:
	World();

	void loadMap(const std::string &backgroundPath, std::map<std::string, std::shared_ptr<Texture>> tileTextures);

	void addPlayer(std::shared_ptr<Entity> e);

	void addEntity(std::shared_ptr<Entity> e);

	void addItem(std::shared_ptr<Entity> e);

	void update(const GameTime& gameTime);

	void draw();

	void setWindowSize(glm::ivec2 windowSize);
private:
	std::vector<unsigned int> m_backGround;
	std::shared_ptr<Entity> m_player;
	std::vector<std::shared_ptr<Entity>> m_items;
	std::vector<std::shared_ptr<Entity>> m_entities;
	std::vector<std::shared_ptr<Entity>> m_updateableEntities;
	std::vector<std::shared_ptr<Entity>> m_background;
	glm::ivec2 m_size;
	glm::ivec2 m_windowSize;
};