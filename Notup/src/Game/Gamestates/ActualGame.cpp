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
#include <Game/GameComponents/Entities/StaticObject.h>

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
	m_world.setWindowSize(m_windowSize);

	return true;
}

bool ActualGame::loadContent()
{
	// loading textures
	std::ifstream pathFile;
	pathFile.open("Maps/paths.txt", std::ios_base::out);
	if (pathFile)
	{
		while (!pathFile.eof())
		{
			std::string line;
			std::string key;
			std::string path;
			bool collidable;

			std::shared_ptr<Texture> texture;
			std::getline(pathFile, line);
			std::istringstream iSs(line);
			iSs >> key >> path >> collidable;

			texture = std::make_shared<Texture>();
			texture->loadTextureFromFile(path);

			tileTextures[key] = texture;
			tileCollidingInformation[key] = collidable;
		}
	}
	pathFile.close();

	std::shared_ptr<Texture> playerTexture = std::make_shared<Texture>();
	playerTexture->loadTextureFromFile("Graphics/Entities/Player.png");
	std::shared_ptr<Texture> backgroundTexture = std::make_shared<Texture>();
	backgroundTexture->loadTextureFromFile("Graphics/background.png");

	Entity::setShaderProgram(m_textureShader);
	m_player = std::make_shared<Player>(m_world, 10.0f, glm::vec2(0), glm::vec2(5, 5), playerTexture, m_input, m_windowSize);
	std::shared_ptr<StaticObject> background = std::make_shared<StaticObject>(m_world, 10.0f, glm::vec2(0), glm::vec2(5, 5), backgroundTexture);

	m_world.loadMap("Maps/map0/", tileTextures);

	//m_world.addEntity(background);
	m_world.addPlayer(m_player);

	return true;
}

GamestateType ActualGame::update()
{
	std::ostringstream osS;
	osS << m_gameTime.getElapsedGameTime();
	glutSetWindowTitle(osS.str().c_str());

	m_world.update(m_gameTime);
	return GamestateType::NONE;
}

void ActualGame::draw()
{
	m_textureShader->use();
	glm::mat4 & modelMatrix = m_textureShader->getMatrixHandler().getMatrix("modelMatrix");
	modelMatrix = glm::translate(glm::mat4(), -glm::vec3(m_player->getPosition(),0) + glm::vec3(m_windowSize,0)/2.0f);
	m_world.draw();
} 

GamestateType ActualGame::getGamestateType() const
{ 
	return GamestateType::GAME;
}