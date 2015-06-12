/**********************************************************************************************
* 										includes
**********************************************************************************************/
#define GLM_FORCE_RADIANS
#include <Framework/Drawable/Model.t>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
/**********************************************************************************************
* 										class definition
**********************************************************************************************/

template<typename VertexType>
Model<VertexType>::Model()
	:m_meshes(),
	m_meshDatas(),
	m_matrials(),
	m_position(0),
	m_rotation(0)
{

}
template<typename VertexType>
void Model<VertexType>::initialize()
{

}

template<typename VertexType>
void Model<VertexType>::addMesh(std::shared_ptr<Mesh<VertexType>> mesh, std::shared_ptr<Material> material, const MeshData &meshData)
{
	m_meshes.push_back(mesh);
	m_matrials.push_back(material);
	m_meshDatas.push_back(meshData);
}

template<typename VertexType>
std::vector<std::shared_ptr<Mesh<VertexType>>>  Model<VertexType>::getMeshes()
{
	return m_meshes;
}


template<typename VertexType>
std::vector<std::shared_ptr<Material>> Model<VertexType>::getMaterials()
{
	return m_matrials;
}

template<typename VertexType>
void Model<VertexType>::draw()
{
	m_shaderProgram->use();

	MatrixHandler &matrixHandler(m_shaderProgram->getMatrixHandler());
	matrixHandler.pushMatrix("modelMatrix");
	glm::mat4 &currentModelMatrix = matrixHandler.getMatrix("modelMatrix");
	glm::mat4 &currentNormalMatrix = matrixHandler.getMatrix("normalMatrix");
	currentModelMatrix = glm::translate(currentModelMatrix, m_position);
	currentModelMatrix = glm::rotate(currentModelMatrix, m_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	currentModelMatrix = glm::rotate(currentModelMatrix, m_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	currentModelMatrix = glm::rotate(currentModelMatrix, m_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

	for (unsigned int i = 0; i < m_meshes.size(); ++i)
	{
		matrixHandler.pushMatrix("modelMatrix");
		matrixHandler.pushMatrix("normalMatrix");
		currentModelMatrix = matrixHandler.getMatrix("modelMatrix");
		currentNormalMatrix = matrixHandler.getMatrix("normalMatrix");
		MeshData &currentMeshData = m_meshDatas[i];
		m_matrials[i]->bind("material", *m_shaderProgram);
		currentNormalMatrix = glm::transpose(glm::inverse(currentModelMatrix));
		m_shaderProgram->updateMatrix("modelMatrix");
		m_shaderProgram->updateMatrix("normalMatrix");
		m_meshes[i]->draw();
		matrixHandler.popMatrix("modelMatrix");
		matrixHandler.popMatrix("normalMatrix");
	}
	matrixHandler.popMatrix("modelMatrix");
}

template<typename VertexType>
void Model<VertexType>::setShaderProgram(std::shared_ptr<ShaderProgram> shaderProgram)
{
	m_shaderProgram = shaderProgram;
	for (unsigned int i = 0; i < m_meshes.size(); ++i)
	{
		m_meshes[i]->setShaderProgram(shaderProgram);
	}
}

template<typename VertexType>
void Model<VertexType>::setPosition(const glm::vec3 &position)
{
	m_position = position;
}

template<typename VertexType>
void Model<VertexType>::setRotation(const glm::vec3 &rotation)
{
	m_rotation = rotation;
}


template<typename VertexType>
void Model<VertexType>::deleteLocalMeshData()
{
	for (int i = 0; i < m_meshes.size(); ++i)
	{
		m_meshes[i].deleteLocalData();
	}
}