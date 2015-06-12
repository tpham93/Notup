#pragma once

/********************************************************************************************** 
* 										includes
**********************************************************************************************/
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <Framework/Game/Game.h>
#include <string>
#include <Framework/Resources/Texture.h>
#include <Framework/Drawable/Sprite.h>
#include <Framework/Drawable/BufferData.h>
#include <Framework/Shader/ShaderProgram.h>
#include <Framework/Shader/MatrixHandler.h>
#include <Game/Gamestates/Gamestate.h>



/********************************************************************************************** 
* 										forward declarations
**********************************************************************************************/
class GameTime;

/********************************************************************************************** 
* 										class declaration
**********************************************************************************************/

/*!
* 	\brief	a derived class of Game which
* 			should handle the game's logic and drawing
*/
class CustomGame : public Game
{
public:
	/*!
	* 	\brief			constructor
	*	\param argc		the number of parameters
	*	\param argv		the parameters as string
	*/
	CustomGame(int argc, char **args);

	/*!
	* 	\brief			destructor
	*/
	~CustomGame();

protected:
	/*!
	* 	\brief			initializing all values (matrices, lists etc.)
	* 	\returns		true if everything was succesful
	* 	\pre			none
	* 	\post			game with initialized values
	* 	\sideeffect		none
	*/
	virtual bool initialize() override;

	/*!
	* 	\brief			loading all the content of the game you need ( models, textures etc.)
	* 	\returns		true if everything was succesful
	* 	\pre			initialize called
	* 	\post			game with loaded content
	* 	\sideeffect		none
	*/
	virtual bool loadContent() override;

	/*!
	* 	\brief			executing the logic of the game
	* 	\param gameTime	the time in which the game should be dependent of
	* 	\returns void
	* 	\pre			initialize() and loadContent() called
	* 	\post			game changed its state from the previous frame to the
	* 					current frame, processing the logic and user's input
	* 	\sideeffect		none
	*/
	virtual void update() override;

	/*!
	* 	\brief			executing the drawing to the window of the game
	* 	\param gameTime	the time in which the game should be dependent of
	* 	\returns void
	* 	\pre			initialize and loadContent and update called at least once
	* 	\post			the new image for the screen should be ready to be displayed
	* 	\sideeffect		the content of the window may change according to what happened in the update
	*/
	virtual void draw() override;
	 
private:

	void switchGamestate(GamestateType nextGamestateType);
	std::shared_ptr<ShaderProgram> m_textureShader;

	GamestateType m_currentGameStateType;
	std::shared_ptr<Gamestate> m_currentGamestate;
	std::shared_ptr<Gamestate> m_pausedGamestate;

	//std::shared_ptr<vrpn_Button_Remote> buttonRemote;
	//std::shared_ptr<vrpn_Analog_Remote> analogRemote;

	//vrpn_float64 analogValue;
	//vrpn_int32 buttons[1];
};