#pragma once

/********************************************************************************************** 
* 										includes
**********************************************************************************************/
#include <memory>
#include <Framework/Resources/Texture.h>
#include <Framework/Helper/Rect.h>
#include <Framework/Drawable/Drawable.h>
#include <Framework/Drawable/BufferData.h>
#include <Framework/VertexData/Vertex2DTex.h>

/********************************************************************************************** 
* 										class declaration
**********************************************************************************************/

/*!
* 	\brief	a class to wrap the drawing of a texture
*/
class Sprite : public Drawable
{
public:
	/*!
	* 	\brief constructor
	*/
	Sprite();

	/*!
	* 	\brief			constructor
	* 	\param texture	the texture you want to draw
	*/
	Sprite(std::shared_ptr<const Texture> texture);

	/*!
	* 	\brief getting the texture of the sprite
	*/
	const Texture &getTexture() const;

	/*!
	* 	\brief			set the texture
	* 					the width and height of the destination is set to the textures width and height if there was no texture before
	* 					the source is set to the whole texture
	* 	\param texture	the texture which should be drawn
	*/
	void setTexture(std::shared_ptr<Texture> texture);

	/*!
	* 	\brief		get the destination
	* 	\return		the position and the size of the drawn texture
	*/
	Rect &getDestination();

	/*!
	* 	/overload const Rect &getDestination() const
	*/
	const Rect &getDestination() const;

	/*!
	* 	\brief				set the destination
	* 	\param destination	the position and the size of the drawn texture
	*/
	void setDestination(Rect destination, bool updateMatrices = true);

	/*!
	* 	\brief			set the destination the current width and height stays the same
	* 	\param position	the position where the texture should be drawn
	*/
	void setDestination(glm::vec2 position, bool updateMatrices = true);

	/*!
	* 	\brief		get the source
	* 	\return		the part of the texture which should be drawn in px
	*/
	Rect &getSource();

	/*!
	* 	/overload const Rect &getSource() const
	*/
	const Rect &getSource() const;

	/*!
	* 	\brief				set the source
	* 	\param destination	the part of the texture which should be drawn in px
	*/
	void setSource(Rect &source);

	/*!
	* 	\brief			set the origin
	* 	\param origin	the point which should be considered as (0/0)
	*/
	void Sprite::setOrigin(glm::vec2 origin, bool updateMatrices = true);

	/*!
	* 	/overload glm::vec2  &Sprite::getOrigin()
	*/
	const glm::vec2 &Sprite::getOrigin() const;

	/*!
	* 	\brief			set the rotation
	* 	\param rotation	the rotation
	*/
	void Sprite::setRotation(float rotation, bool updateMatrices = true);

	/*!
	* 	\brief				get the rotation
	* 	\return rotation	the rotation
	*/
	float Sprite::getRotation() const;

	/*!
	* 	\brief initializing the buffers
	*/
	virtual void initialize() override;

	/*!
	* 	\brief			drawing the texture to the destination
	*/
	virtual void draw();
private:
	/*!
	* 	\brief	updating the matrices
	*/
	void updateMatrices();


	//! the texture you want to draw
	std::shared_ptr<const Texture> m_texture;

	//! the position with the size of the texture
	Rect m_destination;

	//! the position with the size of the texture
	Rect m_source;

	//! the vertices for the texture
	Vertex2DTex m_vertices[4];

	//! the rotation of the texture
	float m_rotation;

	//! transformation of the texture
	glm::mat4 m_modelMatrix;

	glm::vec2 m_origin;
};