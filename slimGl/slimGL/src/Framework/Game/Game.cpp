/********************************************************************************************** 
* 										include
**********************************************************************************************/
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <IL/il.h>
#include <IL/ilu.h>
#include <glm/glm.hpp>
#include <assert.h>
#include <iostream>
#include <Framework/Game/Game.h>
#include <Framework/Helper/Helper.h>
#include <Framework/Resources/Texture.h>
#include <Framework/Resources/Font.h>
#include <Framework/Helper/ModelLoader.h>


/********************************************************************************************** 
* 										declaration
**********************************************************************************************/
Game *Game::activeGame = nullptr;

/********************************************************************************************** 
* 										class definition
**********************************************************************************************/
Game::Game()
	: m_input(nullptr),
	m_windowSize(glm::ivec2())
{
	// check if there is really no game created
	assert(activeGame == nullptr  &&"there must be only a single instance");
	// set the game as the only created game
	activeGame = this;
}

Game::~Game()
{
	// unset the active game
	//activeGame = std::unique_ptr<Game>(nullptr);
}

bool Game::initializeGame(int argc, char** args, glm::ivec2 windowSize, char*  windowTitle, bool captureMouse, bool fullscreen)
{
	// setting the window size
	m_windowSize = windowSize;

	// initialize glut
	glutInit( &argc, args);
	
	// set the version of the opengl context
	glutInitContextVersion(4,2);

	// initialize the display with rgba and double buffer
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

	// set the window size
	glutInitWindowSize(m_windowSize.x, m_windowSize.y);

	// crate the window with the given title
	glutCreateWindow(windowTitle);

	if (fullscreen)
	{
		glutFullScreen();
		m_windowSize = glm::ivec2(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	}
	// set the viewport to the actual size
	glViewport(0, 0, static_cast<GLsizei>(m_windowSize.x), static_cast<GLsizei>(m_windowSize.y));

	// set the clear color to cornflower blue
	glClearColor(100.0f / 255.0f, 149.0f / 255.0f, 237.0f / 255.0f, 1.0f);

	// enabling blending 
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// enable depth test for the correct display of 3d objects
	glDisable(GL_DEPTH_TEST);

	// enable culling
	glDisable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CCW);
	
	// initialize stencil clear value
	glClearStencil(0);

	// initialize depth clear value
	glClearDepth(1);

	Helper::checkGlForError(std::cerr, "Error initializing OpenGl");

	// initialize glew
	glewExperimental = GL_TRUE;
	glewInit();

	// checking for errors manually to catch the errorcode 1280
	// often thrown initializing glew
	GLenum errorCode = glGetError();
	if (errorCode != GL_NO_ERROR  &&errorCode != 1280)
	{
		// an error occured
		std::cerr << gluErrorString(errorCode) << std::endl;
	}

	// initialize the texture class
	Texture::initialize();
	// initialize the Font class
	Font::initialize();
	// initialize the Model loader class
	ModelLoader::initialize(static_cast<float>(m_windowSize.x) / static_cast<float>(m_windowSize.y));

	//initialize the input
	m_input = std::make_shared<Input>(captureMouse, windowSize);

	if (captureMouse)
	{
		glutSetCursor(GLUT_CURSOR_NONE);
	}

	// initialize DevIL
	ilInit();
	ilClearColour(255, 255, 255, 000);

	// check for error
	Helper::checkIlForError(std::cerr, "Couldn't initialize DevIL");

	return true;
}

void Game::run()
{
	// initialize the game
	if (!initialize())
	{
		// error occured
		std::cerr << "initialization failed" << std::endl;
		return;
	}

	// loading content
	if (!loadContent())
	{
		// error occured
		std::cerr << "loading content failed" << std::endl;
		return;
	}

	// set the draw callback method
	glutDisplayFunc(drawWrapper);
	glutIdleFunc(drawWrapper);

	// disable the repeating of keypresses to use glutKeyboardUpFunc
	glutSetKeyRepeat(false);
	
	// set the keyboard callback methods
	glutKeyboardFunc(keyboardDownWrapper);
	glutKeyboardUpFunc(keyboardUpWrapper);

	// set the mouse movement callback methods
	glutMotionFunc(mouseMovementWrapper);
	glutPassiveMotionFunc(mouseMovementWrapper);

	// set the mousebutton callback method
	glutMouseFunc(mouseButtonWrapper);

	// set the mousewheel callback method
	glutMouseWheelFunc(mouseWheelWrapper);

	// set the resize callback method
	glutReshapeFunc(windowReshapeWrapper);

	// initialize the gameTime
	m_gameTime = GameTime(glutGet(GLUT_ELAPSED_TIME), 0, 0);

	// start the first update so the gametime has a correct offset for the time
	updateWrapper(0);

	// start the mainloop
	glutMainLoop();
}

void Game::updateWrapper(int val)
{
	// calculating the time the next update should be called
	int nextExecution = (activeGame->m_fps == 0) ? 0 : 1000 / activeGame->m_fps;

	// update the time
	activeGame->m_gameTime.update(glutGet(GLUT_ELAPSED_TIME));

	// updating the input
	activeGame->m_input->update();

	// drawing the screen
	Game::activeGame->draw();

	// updating the game
	activeGame->update();

	// repeat according the specified fps
	glutTimerFunc(nextExecution, updateWrapper, 0);
}

void Game::drawWrapper()
{
	// swap the buffer to show the drawn screen
	glutSwapBuffers();
}

void Game::keyboardDownWrapper(unsigned char key, int x, int y)
{
	// give the key to the input handler and flag it as clicked
	activeGame->m_input->updateKey(key, true);
}

void Game::keyboardUpWrapper(unsigned char key, int x, int y)
{
	// give the key to the input handler and flag it as released
	activeGame->m_input->updateKey(key, false);
}

void Game::mouseMovementWrapper(int x, int y)
{
	// give the mouseposition to the input handler
	activeGame->m_input->updateMousePosition(x, y);
}

void Game::mouseButtonWrapper(int button, int state, int x, int y)
{
	// check which button got pressed
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		activeGame->m_input->updateMouseButton(MouseButtons::LeftMouseButton, !state);
		break;
	case GLUT_MIDDLE_BUTTON:
		activeGame->m_input->updateMouseButton(MouseButtons::MiddleMouseButton, !state);
		break;
	case GLUT_RIGHT_BUTTON:
		activeGame->m_input->updateMouseButton(MouseButtons::RightMouseButton, !state);
		break;
	default:
		break;
	}
}

void Game::mouseWheelWrapper(int button, int dir, int x, int y)
{
	// give the direction to the input handler
	activeGame->m_input->updateMouseWheel(dir);
}

void Game::windowReshapeWrapper(int x, int y)
{
	// give the direction to the input handler
	activeGame->m_windowSize = glm::ivec2(x,y);
}
