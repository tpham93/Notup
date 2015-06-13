#pragma once

#include <Game/GameComponents/Entities/Entity.h>
#include <Framework/Input/Input.h>


class StaticObject : public Entity
{
public:
	StaticObject(World &world, float radius, glm::vec2 position, glm::vec2 size, std::shared_ptr<Texture> texture);

	virtual void update(const GameTime& gameTime);

	//virtual void draw();
};