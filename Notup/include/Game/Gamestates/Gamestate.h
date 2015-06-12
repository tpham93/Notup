#pragma once

#include <Framework/Input/Input.h>
#include <Framework/Game/GameTime.h>
#include <Game/Gamestates/GamestateType.h>
#include <memory>

class Gamestate
{
public:
	Gamestate(std::shared_ptr<Input>input, const GameTime &gameTime, glm::ivec2 &windowSize);
	virtual bool initialize() = 0;
	virtual bool loadContent() = 0;
	virtual GamestateType update() = 0;
	virtual void draw() = 0;
	virtual GamestateType getGamestateType() const = 0;

protected:
	std::shared_ptr<Input> m_input;
	const GameTime &m_gameTime;
	glm::ivec2 &m_windowSize;
};