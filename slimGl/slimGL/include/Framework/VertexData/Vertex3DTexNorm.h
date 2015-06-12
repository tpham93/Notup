#pragma once

/********************************************************************************************** 
* 										includes
**********************************************************************************************/
#include <Framework/VertexData/Vertex3DTex.h>

/********************************************************************************************** 
* 										class declaration
**********************************************************************************************/

/*!
* 	\brief	a pod struct to wrap up the vertices used for simple models
*/
struct Vertex3DNormTex : public Vertex3DTex
{
	//! the normal of the vertex
	glm::vec3 m_normal;
};
