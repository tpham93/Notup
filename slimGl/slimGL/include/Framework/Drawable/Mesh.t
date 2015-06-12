#pragma once

/**********************************************************************************************
* 										includes
**********************************************************************************************/
#include <vector>
#include <Framework/Resources/Texture.h>
#include <Framework/Drawable/Drawable.h>
#include <Framework/Drawable/BufferData.h>
#include <Framework/Helper/Box.h>

/**********************************************************************************************
* 										class declaration
**********************************************************************************************/
template<typename VertexType>
class Mesh : public Drawable
{
public:
	
	/*!
	* 	\brief constructor
	*/
	Mesh();

	/*!
	* 	\brief		initializing the mesh
	* 	\sideeffect	the created buffer are bound
	*/
	virtual void initialize();

	/*!
	* 	\brief			adding a vertex to the list
	* 	\param vertex	the vertex which shoukd be added
	* 	\pre			none
	* 	\post			vertex will be uploaded the next updateVertices call
	*/
	void addVertex(const VertexType &vertex);

	/*!
	* 	\brief			adding multiple vertices
	* 	/override		void addVertex(std::vector<VertexType> vertices)
	*/
	void addVertex(std::vector<VertexType> &vertices);

	/*!
	* 	\brief			set the indices used for a triangle strip drawcall
	* 	\param vertex	the indices which should be added
	* 	\pre			none
	* 	\post			indices will be uploaded the next uploadData call
	*/
	void setIndices(std::vector<GLuint> indices);

	/*!
	* 	\brief					sending the vertices to the vertex buffer
	* 	\param	deleteData		if true the locally stored vertices will be deleted
	* 	\pre					initialized added vertices
	* 	\post					model can be drawn
	*/
	void uploadData(bool deleteData);

	/*!
	* 	\brief					deleting the local stored vertices and indices
	*/
	void deleteLocalData();

	/*!
	* 	\brief	drawing the object
	* 	\pre	the bound shader has to be ready
	* 	\post	the object is drawn
	*/
	virtual void draw() override;

	/*!
	* 	\brief	getter for the bounding box
	*	\return	the bounding box for the mesh
	*/
	Box getBoundingBox();

	/*!
	* 	\brief	getter for the local stored vertices
	*/
	const std::vector<VertexType>& getVertices() const;

	/*!
	* 	\brief	getter for the local stored vertices
	*/
	std::vector<VertexType>& getVertices();

	/*!
	* 	\brief	getter for the local stored indices
	*/
	const std::vector<GLuint>& getIndices() const;

	/*!
	* 	\brief	getter for the local stored indices
	*/
	std::vector<GLuint>& getIndices();

protected:
	//! the vertices
	std::vector<VertexType> m_vertices;
	//! the vertices
	std::vector<GLuint> m_indices;
	//! number of vertices
	unsigned int m_numVertices;
	//! number of indices
	unsigned int m_numIndices;
	//! the bounding box of the model
	Box m_boundingBox;
};

#include <Framework/Drawable/Mesh.tpp>
