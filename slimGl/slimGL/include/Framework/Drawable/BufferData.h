#pragma once

/********************************************************************************************** 
* 										includes
**********************************************************************************************/
#include <GL/glew.h>

struct BufferData
{
	//! the vertex array id used to identify it from the graphicscard
	GLuint vertexArrayId;

	//! the vertxbuffer id used to identify it from the graphicscard
	GLuint vertexBufferId;

	//! the indexbuffer id used to identify it from the graphicscard
	GLuint indexBufferId;
};
