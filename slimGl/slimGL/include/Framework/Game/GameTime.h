#pragma once


/********************************************************************************************** 
* 										class declaration
**********************************************************************************************/


/*!
* 	\brief handling the time the game runs in
*/
class GameTime
{
public:

	/*!
	* 	\brief	constructor
	* 	\param totalGameTime	the elapsed time since the beginning of the game
	* 	\param elapsedGameTime	the elapsed gametime relatively to the last frame
	* 	\param startTimeOffset	the time elapsed since the game begans
	*/
	GameTime(int startTimeOffset = 0, int totalGameTime = 0, int elapsedGameTime = 0);

	/*!
	* 	\brief	destructor
	*/
	virtual ~GameTime();
	/*!
	* 	\brief				updates the time
	* 	\param currentTime	the new time of the frame
	* 	\pre				none
	* 	\post				a new totalTime and elapsedTime is beig calculated
	*/
	void update(int currentTime);

	/*!
	* 	\brief	gets the total game time
	* 	\return the time passed since the game started
	*/
	int getTotalGameTime() const;

	/*!
	* 	\brief gets the elapsed game time
	* 	\return the time passed since the last frame
	*/
	int getElapsedGameTime() const;

protected:
private:

	//!	the time passed since the game started
	int totalGameTime;

	//!	the time passed since the last frame
	int elapsedGameTime;

	//!	the time passed since the the game began
	int startTimeOffset;
};
