#include <Game/GameComponents/Entities/Entity.h>
#include <Game/GameComponents/World.h>


std::shared_ptr<ShaderProgram> Entity::m_shaderProgram(nullptr);

Entity::Entity(World &world, float radius, glm::vec2 position, glm::vec2 size)
	:m_world(world),
	m_pos(position),
	m_size(size),
	m_alive(true)
{

}

Entity::~Entity()
{

}

void Entity::draw()
{
	m_sprite.draw();
}

void Entity::collision(std::shared_ptr<Entity> e)
{
}

void Entity::setShaderProgram(std::shared_ptr<ShaderProgram> shaderProgram)
{
	m_shaderProgram = shaderProgram;
}

const glm::vec2& Entity::getPosition() const
{
	return m_pos;
}

void Entity::setPosition(glm::vec2 pos)
{
	m_pos = pos;
}

void Entity::setIndex(unsigned int index)
{
	m_index = index;
}

unsigned int &Entity::getIndex()
{
	return m_index;
}
glm::vec2 Entity::getSize()
{
	return m_size;
}
bool Entity::isAlive()
{
	return m_alive;
}
bool Entity::drawNormal()
{
	return true;
}