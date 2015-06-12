#pragma once

/**********************************************************************************************
* 										includes
**********************************************************************************************/
#include <memory>
#include <Framework/Drawable/MeshData.h>
#include <Framework/Drawable/Mesh.t>
#include <Framework/UniformStruct/Material/Material.h>

/**********************************************************************************************
* 										class declaration
**********************************************************************************************/
template<typename VertexType>
class Model : public Drawable
{
public:

	/*!
	* 	\brief constructor
	*/
	Model();

	/*!
	* 	\brief	initializing the model
	* 	\pre	none
	* 	\post	meshes can now be added
	*/
	virtual void initialize();

	/*!
	* 	\brief			adding a mesh to the model
	* 	\param mesh		the mesh which should be added to the model
	* 	\param material	the material which should be used to draw the mesh
	* 	\param meshData	the position and rotation relatively to the origin of the model
	* 	\pre			none
	* 	\post			the model is drawn with the new mesh
	*/
	void addMesh(std::shared_ptr<Mesh<VertexType>> mesh, std::shared_ptr<Material> material, const MeshData &meshData);

	/*!
	* 	\brief	getter for the added meshes
	*	\return	all added meshes
	*/
	std::vector<std::shared_ptr<Mesh<VertexType>>> getMeshes();

	/*!
	* 	\brief	getter for the materials
	*	\return	all added meshes
	*/
	std::vector<std::shared_ptr<Material>> getMaterials();

	/*!
	* 	\brief	drawing the model
	* 	\pre	the bound shader has to be ready
	* 	\post	the object is drawn
	*/
	virtual void draw() override;

	/*!
	* 	\brief					set the shader which should be used to draw
	* 	\param shaderProgram	the shaderprgram you want to use for drawing
	* 	\pre					buffer are initialized
	* 	\post					shader will be used for the following draw calls
	*/
	virtual void setShaderProgram(std::shared_ptr<ShaderProgram> shaderProgram);

	/*!
	*	\brief	set the new position for the model
	*	\param position		the new position of the model
	*/
	void setPosition(const glm::vec3 &position);
	/*!
	*	\brief	set the new rotation for the model
	*	\param position		the new rotation of the model
	*/
	void setRotation(const glm::vec3 &rotation);

	/*!
	*	\brief	deleting the local mesh data of the meshes
	*/
	void deleteLocalMeshData();
protected:
	//! the meshes of the model
	std::vector<std::shared_ptr<Mesh<VertexType>>> m_meshes;
	//! the meshes of the model
	std::vector<MeshData> m_meshDatas;
	//! the materials usd by the meshes
	std::vector<std::shared_ptr<Material>> m_matrials;
	//! the position of the model
	glm::vec3 m_position;
	//! the position of the model
	glm::vec3 m_rotation;
};

#include <Framework/Drawable/Model.tpp>
