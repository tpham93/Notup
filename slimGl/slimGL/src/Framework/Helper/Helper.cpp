/********************************************************************************************** 
* 										include
**********************************************************************************************/
#include <Framework/Helper/Helper.h>
#include <GL/freeglut.h>
#include <IL/il.h>
#include <IL/ilu.h>
#include <assert.h>

/********************************************************************************************** 
* 										class definition
**********************************************************************************************/
bool Helper::checkGlForError(std::ostream &stream, const std::string &errorMessage)
{
	GLenum errorCode = glGetError();
	if (errorCode != GL_NO_ERROR)
	{
		// error occured
  		printError(stream, errorMessage, reinterpret_cast<const char* >(gluErrorString(errorCode)));
		return false;
	}
	return true;
}

bool Helper::checkIlForError(std::ostream &stream, const std::string &errorMessage)
{
	ILenum errorCode = ilGetError();
	if (errorCode != IL_NO_ERROR)
	{
		// error occured
		printError(stream, errorMessage, reinterpret_cast<const char* >(iluErrorString(errorCode)));
		return false;
	}
	return true;
}

void Helper::printError(std::ostream &stream, const std::string &errorMessage, const std::string &errorString)
{
	// error occured
	assert(stream << errorMessage << ": " << errorString << std::endl);
}