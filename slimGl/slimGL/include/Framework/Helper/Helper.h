#pragma once

/********************************************************************************************** 
* 										includes
**********************************************************************************************/
#include <string>
#include <iostream>

/********************************************************************************************** 
* 										class declaration
**********************************************************************************************/

/*!
* 	\brief	an class collecting useful functions being used by multiple classes
*/
class Helper
{
public:
	/*!
	* 	\brief				checking open gl for errors
	* 	\param stream		the stream the message should be streamed to
	* 	\param errorMessage	the message shown if an error occured
	* 	\pre				none
	* 	\post				an error message streamed to the given stream if an error occured
	* 	\sideeffect		the last error gets pulled from open gl
	*/
	static bool checkGlForError(std::ostream &stream, const std::string &errorMessage);

	/*!
	* 	\brief				checking il for errors
	* 	\param stream		the stream the message should be streamed to
	* 	\param errorMessage	the message shown if an error occured
	* 	\pre				none
	* 	\post				an error message streamed to the given stream if an error occured
	* 	\sideeffect		the last error gets pulled from il
	*/
	static bool checkIlForError(std::ostream &stream, const std::string &errorMessage);

private:

	/*!
	* 	\brief				printing the errors to the stream
	* 	\param stream		the stream the message should be streamed to
	* 	\param errorMessage	the message shown if an error occured
	* 	\param errorString	the error as string
	* 	\pre				none
	* 	\post				an error message streamed to the given stream if an error occured
	* 	\sideeffect		the last error gets pulled from il
	*/
	static void printError(std::ostream &stream, const std::string &errorMessage, const std::string &errorString);
};