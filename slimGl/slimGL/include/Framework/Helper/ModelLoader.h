#pragma once

/**********************************************************************************************
* 										includes
**********************************************************************************************/
#include <memory>
#include <assimp/Importer.hpp>
#include <assimp\postprocess.h>
#include <assimp/scene.h>
#include <assimp/DefaultLogger.hpp>
#include <assimp/LogStream.hpp>
#include <Framework/Drawable/Model.t>
#include <Framework/VertexData/Vertex3DTexNorm.h>
#include <Framework/UniformStruct/Material/BasicLightingMaterial.h>

/**********************************************************************************************
* 										class declaration
**********************************************************************************************/

/*!
* 	\brief	a class to wrap the loading of models with assimp
*/
class ModelLoader
{
public:
	/*!
	*	\brief				initializing the ModelLoader class
	*	\param	aspectRatio	the aspect ratio of the screen
	*/
	static void initialize(float aspectRatio);

	/*!
	*	\brief	starting the logging via the console
	*/
	static void startLogging();

	/*!
	*	\brief	ending the logging via the console
	*/
	static void endLogging();

	/*!
	*	\brief					loading a model via a file path
	*	\param	filePath		the path to the model
	*	\param	scale			the scale of the model, which gets premultiplied
	*	\param	deleteLocalData	if true the local data of the meshes will be deleted
	*	\return					the loaded model
	*/
	static std::shared_ptr<Model<Vertex3DNormTex>> load(const std::string &filePath, float scale = 1.0f, bool deleteLocalData = true);

private:
	/*!
	*	\brief			generate an glm vec4 out of aiColor4D
	*	\param value	the aiColor4D you want to transform
	*	\return			the glm vec4 with the same values as the parameter
	*/
	static glm::vec4 aiColor4DToGlmVec4(const aiColor4D &value);
	/*!
	*	\brief			generate an glm mat4 out of aiMatrix4x4
	*	\param value	the aiMatrix4x4 you want to transform
	*	\return			the glm mat4 with the same values as the parameter
	*/
	static glm::mat4 aiMatrix4ToGlmMat4(const aiMatrix4x4 &value);

	/*!
	*	\brief								adding all meshes from the node (including chilren)
	*	\param scene						the scene where to take the textures from
	*	\param currentNode					the node, where the meshes begin
	*	\param model						the model where the meshes should be added to
	*	\param currentNodeTransformation	the transformation of the last node
	*	\param materials					the materials used by the models
	*	\param scale						the scale to resize the model
	*	\return								a map with all textures
	*/
	static void addMeshesFromNode(const aiScene *scene, const aiNode *currentNode, const glm::mat4 &currentNodeTransformation, std::shared_ptr<Model<Vertex3DNormTex>> model, const std::vector<std::shared_ptr<Material>> &materials, float scale, bool deleteLocalData);

	/*!
	*	\brief				loading all textures used by the materials in the scene
	*	\param scene		the scene where to take the textures from
	*	\param modelPath	the path to the model
	*	\return				a map with all textures
	*/
	static std::map<std::string, std::shared_ptr<Texture>> loadTextures(const aiScene *scene, std::string modelPath);

	/*!
	*	\brief			loading all materials in the scene
	*	\param scene	the scene where to take the material from
	*	\return			a vector with all matrials
	*/
	static std::vector<std::shared_ptr<Material>> loadMaterials(const aiScene *scene, std::map<std::string, std::shared_ptr<Texture>> textures);

	/*!
	*	\brief			logging to the console if logging is enabled
	*	\param	msg		the message to log
	*/
	static void log(const std::string& msg);
	//! the importer used by assimp
	static Assimp::Importer importer;
	//! the importer used by assimp
	static bool logging;

static float aspectRatio;
};
