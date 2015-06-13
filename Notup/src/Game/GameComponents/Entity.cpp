#include <Game/GameComponents/Entities/Entity.h>
#include <Game/GameComponents/World.h>


std::shared_ptr<ShaderProgram> Entity::m_shaderProgram(nullptr);

Entity::Entity(World &world, float radius, glm::vec2 position, glm::vec2 size)
	:m_world(world),
	m_pos(position),
	m_size(size)
{

}

Entity::~Entity()
{

}

void Entity::draw()
{
	m_sprite.draw();
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
