#pragma once

#include <Game/GameComponents/Entities/Entity.h>
#include <Framework/Input/Input.h>


class Player : public Entity
{
public:
	Player(World &world, float radius, glm::vec2 position, glm::vec2 size, std::shared_ptr<Texture> texture, std::shared_ptr<Input> input, glm::ivec2 windowSize);

	virtual void update(const GameTime& gameTime);

	//virtual void draw();
private:
	glm::vec2 getMovement();
	void flashLight();

	std::shared_ptr<Input> m_input;
	glm::vec2 m_windowSize;
	float m_energy;
};