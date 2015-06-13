#include <Game/GameComponents/Entities/StaticObject.h>

#include <glm/gtc/constants.hpp>

StaticObject::StaticObject(World &world, float radius, glm::vec2 position, glm::vec2 size, std::shared_ptr<Texture> texture, glm::ivec2 windowSize)
	:Entity(world, radius, position, size)
{
	m_sprite.initialize();
	m_sprite.setShaderProgram(m_shaderProgram);
	m_sprite.setTexture(texture);
	m_sprite.setDestination(position);
	m_sprite.setOrigin(glm::vec2(m_sprite.getTexture().getWidth() / 2, m_sprite.getTexture().getHeight() / 2), false);
	m_sprite.setDestination(glm::vec2(windowSize) / 2.0f, true);
}

void StaticObject::update(const GameTime& gameTime)
{
}