#pragma once

#include <Game/CustomGame.h>
#include <fstream>
#include <Framework/Shader/Shader.h>
#include <glm/gtc/matrix_transform.hpp>
#include <Game/Gamestates/Menu.h>
#include <Game/Gamestates/ActualGame.h>
#include <NvGamepad/NvGamepadXInput.h>
#include <Xinput.h>

CustomGame::CustomGame(int argc, char** argv)
{
	//this->m_fps = 60;
}

CustomGame::~CustomGame()
{
}

bool CustomGame::initialize()
{
	glDisable(GL_DEPTH_TEST);

	m_textureShader = std::make_shared<ShaderProgram>();

	glutSetWindowTitle("");

	

	//buttonRemote = std::make_shared<vrpn_Button_Remote>("openvibe-vrpn@localhost");
	//analogRemote = std::make_shared<vrpn_Analog_Remote>("openvibe-vrpn@localhost");

	//buttonRemote->register_change_handler(this, handle_button);
	//analogRemote->register_change_handler(this, handle_analog);

	return true;
}

bool CustomGame::loadContent()
{
	std::shared_ptr<Shader> fragShader = std::make_shared<Shader>("Shader/texture.frag", GL_FRAGMENT_SHADER);
	std::shared_ptr<Shader> vertexShader = std::make_shared<Shader>("Shader/texture.vert", GL_VERTEX_SHADER);
	std::shared_ptr<MatrixHandler> matrixHandler = std::make_shared<MatrixHandler>();
	matrixHandler->addMatrix("projectionMatrix", glm::ortho<float>(0.0f, static_cast<float>(this->m_windowSize.x), static_cast<float>(this->m_windowSize.y), 0.0f, 1.0f, -1.0f));
	matrixHandler->addMatrix("modelMatrix", glm::mat4(1));
	matrixHandler->addMatrix("viewMatrix", glm::mat4(1));

	fragShader->compile();
	vertexShader->compile();

	m_textureShader->create();
	m_textureShader->attachShader(fragShader);
	m_textureShader->attachShader(vertexShader);
	m_textureShader->link();
	m_textureShader->setMatrixHandler(matrixHandler);
	m_textureShader->use();
	m_textureShader->updateMatrices();

	m_textureShader->addShaderAttribute(ShaderAttributes(m_textureShader->getAttributeLocation("vertexPos2D"), sizeof(Vertex2DTex), GL_FLOAT, 2, reinterpret_cast<GLvoid*>(offsetof(Vertex2DTex, m_position))));
	m_textureShader->addShaderAttribute(ShaderAttributes(m_textureShader->getAttributeLocation("textureCoord"), sizeof(Vertex2DTex), GL_FLOAT, 2, reinterpret_cast<GLvoid*>(offsetof(Vertex2DTex, m_texCoord))));

	switchGamestate(GamestateType::GAME);

	return true;
}

void CustomGame::update()
{

	static bool debug = false;
	if (m_input->keyClicked(static_cast<char>(27)))
	{
		glutLeaveMainLoop();
	}

	


	GamestateType nextGamestateType(m_currentGamestate->update());
	if (nextGamestateType != GamestateType::NONE)
	{
		switchGamestate(nextGamestateType);
	}
}

void CustomGame::switchGamestate(GamestateType nextGamestateType)
{
	switch (nextGamestateType)
	{
	case GamestateType::MENU:
		m_currentGamestate = std::make_shared<Menu>(m_input, m_gameTime, m_windowSize, m_textureShader);
		m_currentGamestate->initialize();
		m_currentGamestate->loadContent();
		break;
	case GamestateType::GAME:
		m_currentGamestate = std::make_shared<ActualGame>(m_input, m_gameTime, m_windowSize, m_textureShader);
		m_currentGamestate->initialize();
		m_currentGamestate->loadContent();
		break;
	case GamestateType::NONE:
	default:
		break;
	}
	m_currentGameStateType = nextGamestateType;
}

#include <Framework/Helper/Helper.h>
void CustomGame::draw()
{
	glClear(GL_COLOR_BUFFER_BIT);

	m_currentGamestate->draw();
	 
	Helper::checkGlForError(std::cout, "OpenGl Error");
}

//void VRPN_CALLBACK CustomGame::handle_analog(void *userdata, vrpn_ANALOGCB b)
//{
//	//std::cout << i << ": " << b.channel[i] << std::endl;
//}
//
//void VRPN_CALLBACK CustomGame::handle_button(void *userdata, vrpn_BUTTONCB b)
//{
//	//std::cout << "Button: " << b.button << ": " << b.state << std::endl;
//}