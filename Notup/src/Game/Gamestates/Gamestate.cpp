#include <Game/Gamestates/Gamestate.h>

Gamestate::Gamestate(std::shared_ptr<Input>input,const GameTime &gameTime,glm::ivec2 &windowSize)
	:m_input(input),
	m_gameTime(gameTime),
	m_windowSize(windowSize)
{

}