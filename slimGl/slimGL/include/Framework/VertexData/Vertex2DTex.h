#pragma once

/********************************************************************************************** 
* 										includes
**********************************************************************************************/
#include <glm/glm.hpp>

/********************************************************************************************** 
* 										class declaration
**********************************************************************************************/

/*!
* 	\brief	a pod struct to wrap up the vertices used mostly for textures
*/
struct Vertex2DTex
{
	//!	the position on the screen
	glm::vec2 m_position;

	//! the coordinate for the texture
	glm::vec2 m_texCoord;
};
