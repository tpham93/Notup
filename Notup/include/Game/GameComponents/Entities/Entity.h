#pragma once

#include<vector>
#include<Framework/Game/GameTime.h>
#include<Framework/Drawable/Sprite.h>

class World;

class Entity
{

public:
	Entity(World &world, float radius);

	virtual ~Entity();

	virtual void update(GameTime& gameTime) = 0;

	virtual void draw();

private:
	World& m_world;
	Sprite m_sprite;
};
