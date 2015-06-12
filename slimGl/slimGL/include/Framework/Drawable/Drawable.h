#pragma once

/********************************************************************************************** 
* 										includes
**********************************************************************************************/
#include <memory>
#include <Framework/Drawable/BufferData.h>

/********************************************************************************************** 
* 										forward declaration
**********************************************************************************************/
class ShaderProgram;

/********************************************************************************************** 
* 										class declaration
**********************************************************************************************/

/*!
* 	\brief	a class to wrap the drawing of a texture
*/
class Drawable
{
public:
	/*!
	* 	\brief constructor
	*/
	Drawable();

	/*!
	* 	\brief destructor
	* 			deletes the buffer if there is any
	*/
	virtual ~Drawable();

	/*!
	* 	\brief		initializing the buffers
	* 	\sideeffect	the created buffer are bound
	*/
	virtual void initialize() = 0;

	/*!
	* 	\brief					set the shader which should be used to draw
	* 	\param shaderProgram	the shaderprgram you want to use for drawing
	* 	\pre					buffer are initialized
	* 	\post					shader will be used for the following draw calls
	*/
	virtual void setShaderProgram(std::shared_ptr<ShaderProgram> shaderProgram);

	/*!
	* 	\brief	drawing the object
	* 	\pre	the bound shader has to be ready
	* 	\post	the object is drawn
	*/
	virtual void draw() = 0;

protected:
	//! the ids for the buffer
	BufferData m_bufferData;

	//! the shader used to draw the things
	std::shared_ptr<ShaderProgram> m_shaderProgram;
};
