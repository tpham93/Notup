#pragma once

#include<vector>
#include<Framework/Game/GameTime.h>
#include<Framework/Drawable/Sprite.h>

class World;

enum class EntityType
{
	Player,
	Background,
	Enemy,
	Spawner
};

class Entity
{

public:
	Entity(World &world, float radius, glm::vec2 position, glm::vec2 size);

	virtual ~Entity();

	virtual void update(const GameTime& gameTime) = 0;

	virtual void draw();

	static void setShaderProgram(std::shared_ptr<ShaderProgram> shaderProgram);

	const glm::vec2& getPosition() const;

	void setPosition(glm::vec2 pos);

	void setIndex(unsigned int index);

	unsigned int &getIndex();

	virtual void collision(std::shared_ptr<Entity> e);

	glm::vec2 getSize();

	bool isAlive();

	virtual bool drawNormal();

protected:
	static std::shared_ptr<ShaderProgram> m_shaderProgram;

	World& m_world;
	Sprite m_sprite;
	float m_radius;
	glm::vec2 m_pos;
	glm::vec2 m_size;
	unsigned int m_index;
	bool m_alive;
};
