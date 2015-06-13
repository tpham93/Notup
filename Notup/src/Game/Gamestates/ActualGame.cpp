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
#include <Game/GameComponents/Entities/Player.h>

ActualGame::ActualGame(std::shared_ptr<Input>input, const GameTime &gameTime, glm::ivec2 &windowSize, std::shared_ptr<ShaderProgram> textureShader)
	: Gamestate(input, gameTime, windowSize),
	m_textureShader(textureShader),
	m_world()
{
}

ActualGame::~ActualGame()
{
}

bool ActualGame::initialize()
{
	glutSetWindowTitle("Game");

	std::shared_ptr<Texture> texture = std::make_shared<Texture>();
	texture->loadTextureFromFile("Graphics/Player.png");

	Entity::setShaderProgram(m_textureShader);
	std::shared_ptr<Player> player = std::make_shared<Player>(m_world, 10.0f, glm::vec2(0), glm::vec2(5,5), texture, m_input, m_windowSize);
	
	m_world.addEntity(player);

	return true;
}

bool ActualGame::loadContent()
{
	return true;
}

GamestateType ActualGame::update()
{

	m_world.update(m_gameTime);
	return GamestateType::NONE;
}

void ActualGame::draw()
{
	m_world.draw();
} 

GamestateType ActualGame::getGamestateType() const
{ 
	return GamestateType::GAME;
}