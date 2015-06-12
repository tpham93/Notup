#pragma once

/********************************************************************************************** 
* 										includes
**********************************************************************************************/
#include <map>
#include <stack>
#include <string>
#include <glm/glm.hpp>

/********************************************************************************************** 
* 										class declaration
**********************************************************************************************/
class MatrixHandler
{
public:
	/*!
	* 	\brief standard constructor
	*/
	MatrixHandler();

	/*!
	* 	\brief			adds a new matrix
	* 	\param name		the name of the matrix you want to store
	* 	\param matrix	the matrix you want to store
	* 	\return			the new created matrix
	* 	\pre			none
	* 	\post			a new matrix will be added and returned
	*/
	glm::mat4 &addMatrix(const std::string &name, const glm::mat4 &matrix = glm::mat4());

	/*!
	*	\brief			pushing the current matrix to the stack
	*	\param name		the name of the matrix
	*/
	void pushMatrix(std::string name);

	/*!
	*	\brief			popping the current matrix from the stack
	*	\param name		the name of the matrix
	*/
	void popMatrix(std::string name);

	/*!
	* 	\brief			gets the matrix with the given name
	* 	\param name		the name of the matrix
	* 	\return			the matrix with the same name
	* 	\pre			a matrix with the same name has to be added before
	* 	\post			none
	*/
	glm::mat4 &getMatrix(std::string name);

	/*!
	* 	/overload	const glm::mat4 &getMatrix(std::string name) const
	*/
	const glm::mat4 &getMatrix(std::string name) const;

	/*!
	* 	\brief			all added matrices with their name
	* 	\return			a map with the matrices
	*/
	std::map<std::string, std::stack<glm::mat4>> &getMatrices();

	/*!
	*	/overload	const std::map<std::string, glm::mat4> getMatrices() const
	*/
	const std::map<std::string, std::stack<glm::mat4>> &getMatrices() const;

	/*!
	* 	\brief			gets the number of matrices
	* 	\return			the number of matrices
	*/
	size_t getMatrixNumber();

private:
	//! the stored matrices
	std::map<std::string, std::stack<glm::mat4>> m_matrices;
};
