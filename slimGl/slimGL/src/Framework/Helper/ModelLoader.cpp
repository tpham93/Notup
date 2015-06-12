/**********************************************************************************************
* 										includes
**********************************************************************************************/

#include <Framework/Helper/ModelLoader.h>

#include <fstream>
#include <sstream>
#include <limits>

/**********************************************************************************************
* 										class definition
**********************************************************************************************/

Assimp::Importer ModelLoader::importer;
bool ModelLoader::logging = false;
float ModelLoader::aspectRatio = 1.0f;


void ModelLoader::initialize(float aspectRatio)
{
	ModelLoader::aspectRatio = aspectRatio;
}


void ModelLoader::startLogging()
{
	Assimp::Logger::LogSeverity severity(Assimp::Logger::VERBOSE);
	Assimp::DefaultLogger::create("", severity, aiDefaultLogStream_STDOUT);
	Assimp::DefaultLogger::get()->info("ModelLoader logging started.");

	logging = true;
}

void ModelLoader::endLogging()
{
	Assimp::DefaultLogger::kill();

	logging = false;
}

void ModelLoader::log(const std::string &msg)
{
	if (logging)
	{
		Assimp::DefaultLogger::get()->info(msg);
	}
}

glm::vec4 ModelLoader::aiColor4DToGlmVec4(const aiColor4D &value)
{
	return glm::vec4(value.r, value.g, value.b, value.a);
}

glm::mat4 ModelLoader::aiMatrix4ToGlmMat4(const aiMatrix4x4 &value)
{
	glm::mat4 to;
	to[0][0] = value.a1; to[1][0] = value.a2;
	to[2][0] = value.a3; to[3][0] = value.a4;
	to[0][1] = value.b1; to[1][1] = value.b2;
	to[2][1] = value.b3; to[3][1] = value.b4;
	to[0][2] = value.c1; to[1][2] = value.c2;
	to[2][2] = value.c3; to[3][2] = value.c4;
	to[0][3] = value.d1; to[1][3] = value.d2;
	to[2][3] = value.d3; to[3][3] = value.d4;

	return to;
}


void ModelLoader::addMeshesFromNode(const aiScene *scene, const aiNode *currentNode,const glm::mat4 &currentNodeTransformation, std::shared_ptr<Model<Vertex3DNormTex>> model,const std::vector<std::shared_ptr<Material>> &materials, float scale, bool deleteLocalData)
{

	glm::mat4 nodeTransformation(currentNodeTransformation * aiMatrix4ToGlmMat4(currentNode->mTransformation));
	for (unsigned int meshIndex = 0; meshIndex < currentNode->mNumMeshes; ++meshIndex)
	{
		const aiMesh* mesh = scene->mMeshes[currentNode->mMeshes[meshIndex]];
		std::shared_ptr<Mesh<Vertex3DNormTex>> currentGeneratedMesh(std::make_shared<Mesh<Vertex3DNormTex>>());
		currentGeneratedMesh->initialize();
		std::vector<unsigned int> indices;

		for (unsigned int faceIndex = 0; faceIndex < mesh->mNumFaces; ++faceIndex)
		{
			const aiFace *face(&mesh->mFaces[faceIndex]);
			
			for (unsigned int i = 0; i < face->mNumIndices; ++i)
			{
				unsigned int currentIndex = face->mIndices[i];
				indices.push_back(currentIndex);
			}
		}
		
		for (unsigned int vertexIndex = 0; vertexIndex < mesh->mNumVertices; ++vertexIndex)
		{
			Vertex3DNormTex currentVertex;

			currentVertex.m_position.x = mesh->mVertices[vertexIndex].x;
			currentVertex.m_position.y = mesh->mVertices[vertexIndex].y;
			currentVertex.m_position.z = mesh->mVertices[vertexIndex].z;
			currentVertex.m_position = glm::vec3(nodeTransformation * glm::vec4(currentVertex.m_position, 1));

			if (mesh->HasNormals())
			{
				currentVertex.m_normal.x = mesh->mNormals[vertexIndex].x;
				currentVertex.m_normal.y = mesh->mNormals[vertexIndex].y;
				currentVertex.m_normal.z = mesh->mNormals[vertexIndex].z;
				currentVertex.m_normal = glm::normalize(glm::vec3(glm::transpose(glm::inverse(nodeTransformation)) * glm::vec4(currentVertex.m_normal, 0)));
			}

			if (mesh->HasTextureCoords(0))
			{
				currentVertex.m_texCoord.x = mesh->mTextureCoords[0][vertexIndex].x;
				currentVertex.m_texCoord.y = mesh->mTextureCoords[0][vertexIndex].y;
			}

			currentGeneratedMesh->addVertex(currentVertex);
		}

		currentGeneratedMesh->setIndices(indices);
		currentGeneratedMesh->uploadData(deleteLocalData);

		std::shared_ptr<Material> currentGeneratedMaterial(materials[mesh->mMaterialIndex]);

		MeshData meshData;
		meshData.position = glm::vec3(0, 0, 0);


		model->addMesh(currentGeneratedMesh, currentGeneratedMaterial, meshData);
	}

	for (unsigned int childIndex = 0; childIndex < currentNode->mNumChildren; ++childIndex)
	{
		addMeshesFromNode(scene, currentNode->mChildren[childIndex], nodeTransformation, model, materials, scale, deleteLocalData);
	}
}

std::shared_ptr<Model<Vertex3DNormTex>> ModelLoader::load(const std::string &filePath, float scale, bool deleteLocalData)
{
	std::ifstream f(filePath);
	if (f.fail())
	{
		std::ostringstream oStringStream;
		oStringStream << "couldn't open " << filePath << std::endl;
		log(oStringStream.str());
		return std::shared_ptr<Model<Vertex3DNormTex>>();
	}
	else
	{
		f.close();
	}

	const aiScene *scene = importer.ReadFile(filePath.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene == nullptr)
	{
		log(importer.GetErrorString());
	}

	std::map<std::string, std::shared_ptr<Texture>> textures(loadTextures(scene, filePath));

	std::vector<std::shared_ptr<Material>> materials(loadMaterials(scene, textures));


	const aiNode *rootNode = scene->mRootNode;

	std::shared_ptr<Model<Vertex3DNormTex>> output(std::make_shared<Model<Vertex3DNormTex>>());

	addMeshesFromNode(scene, rootNode, glm::scale(glm::mat4(), glm::vec3(scale)), output, materials, scale, deleteLocalData);

	return output;
}

std::map<std::string, std::shared_ptr<Texture>> ModelLoader::loadTextures(const aiScene *scene, std::string modelPath)
{
	std::map<std::string, std::shared_ptr<Texture>> output;

	for (unsigned int materialIndex = 0; materialIndex < scene->mNumMaterials; ++materialIndex)
	{
		aiString texturePath;

		const aiMaterial *material = scene->mMaterials[materialIndex];
		std::shared_ptr<Texture> texture(std::make_shared<Texture>());

		if (AI_SUCCESS == material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath))
		{
			std::string path(texturePath.data);
			std::string loadingPath(modelPath);
			size_t pos = loadingPath.find_last_of("///");
			loadingPath = ((std::string::npos == pos) ? "" : loadingPath.substr(0, pos + 1)) + texturePath.data;
			texture->loadTextureFromFile(loadingPath);
			output[path] = texture;
		}
	}
	return output;
}
#include <iostream>
std::vector<std::shared_ptr<Material>> ModelLoader::loadMaterials(const aiScene* scene, std::map<std::string, std::shared_ptr<Texture>> textures)
{
	std::vector<std::shared_ptr<Material>> output;
	for (unsigned int materialIndex = 0; materialIndex < scene->mNumMaterials; ++materialIndex)
	{
		std::shared_ptr<BasicLightingMaterial> currentGeneratedMaterial(std::make_shared<BasicLightingMaterial>());

		const aiMaterial *material = scene->mMaterials[materialIndex];
		aiColor4D aiDiffuse;
		aiColor4D aiSpecular;
		aiColor4D aiAmbient;
		aiColor4D aiEmission;
		glm::vec4 diffuse(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec4 specular(0.0f, 0.0f, 0.0f, 0.0f);
		glm::vec4 ambient(0.0f, 0.0f, 0.0f, 1.0f);
		glm::vec4 emission(0.0f, 0.0f, 0.0f, 0.0f);
		float shininess;
		float shininessStrength;
		unsigned int max = 1;
		aiString texturePath;
		std::shared_ptr<Texture> texture(std::make_shared<Texture>());

		if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &aiDiffuse))
		{
			diffuse = aiColor4DToGlmVec4(aiDiffuse);
		}
		if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &aiSpecular))
		{
			specular = aiColor4DToGlmVec4(aiSpecular);
		}
		if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &aiAmbient))
		{
			ambient = aiColor4DToGlmVec4(aiAmbient);
		}
		if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_EMISSIVE, &aiEmission))
		{
			emission = aiColor4DToGlmVec4(aiEmission);
		}

		aiGetMaterialFloatArray(material, AI_MATKEY_SHININESS, &shininess, &max);
		aiGetMaterialFloatArray(material, AI_MATKEY_SHININESS_STRENGTH, &shininessStrength, &max);
		shininess *= shininessStrength;

		if (AI_SUCCESS == material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath))
		{
			std::string path(texturePath.data);
			texture = textures[path];
		}
		
		currentGeneratedMaterial->setDiffuse(diffuse);
		currentGeneratedMaterial->setSpecular(specular);
		currentGeneratedMaterial->setAmbient(ambient);
		currentGeneratedMaterial->setEmission(emission);
		currentGeneratedMaterial->setShininess(shininess);
		currentGeneratedMaterial->setTexture(texture);

		output.push_back(currentGeneratedMaterial);
	}
	return output;
}