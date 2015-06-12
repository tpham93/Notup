#pragma once

/********************************************************************************************** 
* 										includes
**********************************************************************************************/
#include <memory>
#include <Framework/Game/GameTime.h>
#include <Framework/Input/Input.h>
#include <glm/glm.hpp>


/********************************************************************************************** 
* 										class declaration
**********************************************************************************************/

/*!
* 	\brief	a pure virtual class describing the basic handling
* 			of updating and drawing of the game
*/
class Game
{
public:
	/*!
	* 	\brief	copies are not allowed!
	*/
	Game(const Game &game) = delete;

	/*!
	* 	\brief	assignments aren't allowed!
	*/
	Game &operator=(const Game &game) = delete;


	/*!
	* 	\brief			standard constructor
	* 	\pre			no previous game created otherwise an assertion will fail
	* 	\post			see constructor of derived classes
	* 	\sideeffect	activeGame is set
	*/
	Game();

	/*!
	* 	\brief			destructor
	* 	\pre			none
	* 	\post			see destructor of derived classes
	* 	\sideeffect	activeGame will be unset
	*/
	virtual ~Game();

	/*!
	* 	\brief				initializing the components the game needs (window, opengl context etc.)
	* 	\param argc			the number of arguments
	* 	\param args			the arguments the program got called with 
	* 	\param windowSize	the size for the window in pixel
	* 	\param windowTitle	the title of the window in which the game is shown 
	*	\param captureMouse	true if the mouse should be captured inside the window
	*	\param captureMouse	true if the game should start in fullscreen
	* 	\returns			true if everything was successful
	* 	\pre				initializes the basic components and calls initialize of the derived class
	* 	\post				internal state of game may change, look into the overriden method
	* 	\sideeffect		window is created but invisible, context is created too
	*/
	bool initializeGame(int argc, char** args, glm::ivec2 windowSize, char*  windowTitle, bool captureMouse, bool fullscreen);

	/*!
	* 	\brief			gets the game ready and starts its mainloop
	* 	\pre			uninitialized game
	* 	\post			mainloop started
	* 	\sideeffect		\sa update
	* 					\sa draw
	*/
	void run();

	/*!
	* 	\brief			initializing all values (matrices, lists etc.)
	* 	\returns		true if everything was succesful
	* 	\pre			see initialize of derived classes
	* 	\post			see initialize of derived classes
	* 	\sideeffect	see initialize of derived classes
	*/
	virtual bool initialize() = 0;

	/*!
	* 	\brief			loading all the content of the game you need ( models, textures etc.)
	* 	\returns		true if everything was succesful
	* 	\pre			see loadContent of derived classes
	* 	\post			see loadContent of derived classes
	* 	\sideeffect	see loadContent of derived classes
	*/
	virtual bool loadContent() = 0;

	/*!
	* 	\brief			executing the logic of the game
	* 	\pre			initialize() and loadContent() called
	* 	\pre			see update of derived classes
	* 	\post			see update of derived classes
	* 	\sideeffect	see update of derived classes
	*/
	virtual void update() = 0;

	/*!
	* 	\brief			executing the drawing to the window of the game
	* 	\pre			initialize and loadContent and update called at least once
	* 	\post			internal state of game may change, look into the overriden method
	* 	\sideeffect	the content of the window may change according to what happened in the update
	*/
	virtual void draw() = 0;

protected:
	//! the input handler for the game
	std::shared_ptr<Input> m_input;

	//! the time the game runs in 
	GameTime m_gameTime;

	//! the size of the window
	glm::ivec2 m_windowSize;

	//! the fps the game should have (not guaranteed)
	int m_fps;
private:

	/*!
	* 	\brief		callback function handling the update method of the derived class
	* 	\param val	needed for gluttimerfunc
	*/
	static void updateWrapper(int val);

	/*!
	* 	\brief		callback function handling the drawing method of the derived class
	*/
	static void drawWrapper();

	/*!
	* 	\brief		callback function handling the key presses
	* 	\param key	the ascii code of the pressed key
	* 	\param x	the new x coordinate of the mouse
	* 	\param y	the new y coordinate of the mouse
	*/
	static void keyboardDownWrapper(unsigned char key, int x, int y);

	/*!
	* 	\brief		callback function handling the key releases
	* 	\param key	the ascii code of the pressed key
	* 	\param x	the new x coordinate of the mouse
	* 	\param y	the new y coordinate of the mouse
	*/
	static void keyboardUpWrapper(unsigned char key, int x, int y);

	/*!
	* 	\brief		callback function handling the mousemovement
	* 	\param x	the new x coordinate of the mouse
	* 	\param y	the new y coordinate of the mouse
	*/
	static void mouseMovementWrapper(int x, int y);

	/*!
	* 	\brief			callback function handling the mousebuttons
	* 	\param button	the button corresponding to the callback
	* 	\param state	the state which tells whether the button is released or clicked
	* 	\param x		the current x coordinate of the mouse
	* 	\param y		the current y coordinate of the mouse
	*/
	static void mouseButtonWrapper(int button, int state, int x, int y);

	/*!
	* 	\brief			callback function handling the mousewheel
	* 	\param button	the button corresponding to the callback
	* 	\param dir		the	direction of the mousewheel
	* 	\param x		the current x coordinate of the mouse
	* 	\param y		the current y coordinate of the mouse
	*/
	static void mouseWheelWrapper(int button, int dir, int x, int y);

	/*!
	* 	\brief			callback function handling the window reshape
	* 	\param x		the new width pf the window
	* 	\param y		the new width pf the window
	*/
	static void windowReshapeWrapper(int x, int y);

	//! the only constructed game instance
	static Game *activeGame;
};
