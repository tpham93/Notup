/********************************************************************************************** 
* 										includes
**********************************************************************************************/
#include <Framework/Shader/MatrixHandler.h>

/********************************************************************************************** 
* 										class definition
**********************************************************************************************/


MatrixHandler::MatrixHandler()
	:m_matrices()
{
}

glm::mat4 &MatrixHandler::addMatrix(const std::string &name, const glm::mat4 &matrix)
{
	m_matrices.emplace(std::make_pair(name,std::stack<glm::mat4>()));
	m_matrices[name].push(matrix);
	return m_matrices[name].top();
}

void MatrixHandler::pushMatrix(std::string name)
{
	m_matrices[name].push(m_matrices[name].top());
}

void MatrixHandler::popMatrix(std::string name)
{
	assert(m_matrices.size() > 1 && "Stack is empty!");
	m_matrices[name].pop();
}

glm::mat4 &MatrixHandler::getMatrix(std::string name)
{
	return m_matrices[name].top();
}

const glm::mat4 &MatrixHandler::getMatrix(std::string name) const
{
	return m_matrices.find(name)->second.top();
}

std::map<std::string, std::stack<glm::mat4>> &MatrixHandler::getMatrices()
{
	return m_matrices;
}

const std::map<std::string, std::stack<glm::mat4>> &MatrixHandler::getMatrices() const
{
	return m_matrices;
}

size_t MatrixHandler::getMatrixNumber()
{
	return m_matrices.size();
}