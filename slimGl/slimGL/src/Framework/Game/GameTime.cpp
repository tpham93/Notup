/********************************************************************************************** 
* 										include
**********************************************************************************************/
#include <Framework/Game/GameTime.h>

/********************************************************************************************** 
* 										class definition
**********************************************************************************************/
GameTime::GameTime(int startTimeOffset, int totalGameTime, int elapsedGametime)
	: totalGameTime(totalGameTime),
	elapsedGameTime(elapsedGametime),
	startTimeOffset(startTimeOffset)
{
}

GameTime::~GameTime()
{

}

void GameTime::update(int currentTime)
{
	// saving the old total gametime
	int tmp = totalGameTime;
	// calculate the new total gametime
	totalGameTime = currentTime - startTimeOffset;
	// calculate the new elapsed gametime
	elapsedGameTime = totalGameTime - tmp;
}

int GameTime::getTotalGameTime() const
{
	return totalGameTime;
}

int GameTime::getElapsedGameTime() const
{
	return elapsedGameTime;
}
