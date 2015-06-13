#include <Game/GameComponents/Entities/StaticObject.h>

#include <glm/gtc/constants.hpp>
#include <Game/Constants.h>

StaticObject::StaticObject(World &world, float radius, glm::vec2 position, glm::vec2 size, std::shared_ptr<Texture> texture)
	:Entity(world, radius, position, size)
{
	m_sprite.initialize();
	m_sprite.setShaderProgram(m_shaderProgram);
	m_sprite.setTexture(texture);
	Rect r(position.x, position.y, Constants::TILE_SIZE.x, Constants::TILE_SIZE.y);
	m_sprite.setDestination(r);
	m_sprite.setOrigin(glm::vec2(m_sprite.getTexture().getWidth() / 2, m_sprite.getTexture().getHeight() / 2), false);
	m_sprite.setDestination(position, true);
}

void StaticObject::update(const GameTime& gameTime)
{
}