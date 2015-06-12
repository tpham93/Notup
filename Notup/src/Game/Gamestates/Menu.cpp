#include <Game/Gamestates/Menu.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/gtc/constants.hpp>

Menu::Menu(std::shared_ptr<Input>input, const GameTime &gameTime, glm::ivec2 &windowSize, std::shared_ptr<ShaderProgram> textureShader)
	: Gamestate(input, gameTime, windowSize),
	m_textureShader(textureShader)
{

}

bool Menu::initialize()
{
	glutSetWindowTitle("MENU");

	return true;
}

bool Menu::loadContent()
{
	//// create the textures and the font
	//std::shared_ptr<Texture> arrowTexture(std::make_shared<Texture>());
	//std::shared_ptr<Font> fontBig(std::make_shared<Font>());
	//std::shared_ptr<Font> fontSmall(std::make_shared<Font>());

	//// loading the arrow image, set the texture and the shader to the sprite
	//arrowTexture->loadTextureFromFile("Graphics/arrow.png");
	//m_arrow.setShaderProgram(m_textureShader);
	//m_arrow.setTexture(arrowTexture);

	//// loading the font with 2 different sizes
	//fontBig->load("Font/HOMOARAK.TTF", 100);
	//fontSmall->load("Font/HOMOARAK.TTF", 30);
	//// set the fonts which should be used by the displayed texts
	//m_textMainMenu.setFont(fontBig);
	//m_textKey.setFont(fontSmall);
	//// set the shader
	//m_textMainMenu.setShaderProgram(m_textureShader);
	//m_textKey.setShaderProgram(m_textureShader);

	//// the texts to display
	//std::string mainMenu = "Main Menu";
	//std::string key = "Press Key to Start";

	//// measure the size of the texts
	//glm::uvec2 mainMenuSize = fontBig->getStringSize(mainMenu);
	//glm::uvec2 keySize = fontSmall->getStringSize(key);

	//// calculate the positions
	//glm::vec2 mainMenuPos = glm::vec2(m_windowSize.x * 0.5f, m_windowSize.y * 0.25f) - glm::vec2(mainMenuSize) / 2.0f;
	//glm::vec2 keyPos = glm::vec2(m_windowSize.x * 0.5f, m_windowSize.y * 0.60f) - glm::vec2(keySize) / 2.0f;

	//// set the positions
	//m_textMainMenu.setDestination(mainMenuPos);
	//m_textKey.setDestination(keyPos);

	//// set the texts
	//m_textKey.setText(key);
	//m_textMainMenu.setText(mainMenu);

	//// calculate and set the position for the arrow
	//m_arrowStartPosition = glm::vec2(m_windowSize.x * 0.5f, m_windowSize.y * 0.9f) - glm::vec2(m_arrow.getTexture().getWidth() / 2.0f, m_arrow.getTexture().getHeight());
	//m_arrow.setDestination(m_arrowStartPosition);

	return true;
}

GamestateType Menu::update()
{
	// get input to switch the gamestate
	if (m_input->getPressedKeys().size() > 0)
	{
		return GamestateType::GAME;
	}

	return GamestateType::NONE;
}

void Menu::draw()
{
	// fill screen with white color
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);
}

GamestateType Menu::getGamestateType() const
{
	return GamestateType::MENU;
}
