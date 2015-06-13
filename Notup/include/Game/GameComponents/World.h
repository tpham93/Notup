#pragma once

#include<vector>
#include<Framework/Game/GameTime.h>
#include<glm/glm.hpp>

#include<Game/GameComponents/Entities/Entity.h>

class World
{
public:
	World();

	World(std::string background, std::string items);

	World(std::vector<unsigned int> &background, std::vector<Entity> &items);

	void addEntity(std::shared_ptr<Entity> e);

	void addItem(std::shared_ptr<Entity> e);

	void update(const GameTime& gameTime);

	void draw();
private:
	std::vector<unsigned int> m_backGround;
	std::vector<std::shared_ptr<Entity>> m_items;
	std::vector<std::shared_ptr<Entity>> m_entities;
	glm::vec2 m_size;
};