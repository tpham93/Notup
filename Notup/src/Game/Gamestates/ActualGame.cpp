#include <Game/Gamestates/ActualGame.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <Framework/Shader/Shader.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

#include <fstream>
#include <iostream> 
#include <sstream>  
#include <iomanip>

#include <Framework/Helper/Helper.h>

ActualGame::ActualGame(std::shared_ptr<Input>input, const GameTime &gameTime, glm::ivec2 &windowSize, std::shared_ptr<ShaderProgram> textureShader)
	: Gamestate(input, gameTime, windowSize),
	m_textureShader(textureShader)
{
}

ActualGame::~ActualGame()
{
}

bool ActualGame::initialize()
{


	return true;
}

bool ActualGame::loadContent()
{

	return true;
}

GamestateType ActualGame::update()
{

	return GamestateType::NONE;
}

void ActualGame::draw()
{

} 

GamestateType ActualGame::getGamestateType() const
{ 
	return GamestateType::GAME;
}