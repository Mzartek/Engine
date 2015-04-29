#include <Engine/StaticModel.hpp>
#include <Engine/StaticMesh.hpp>
#include <Engine/Buffer.hpp>
#include <Engine/ShaderProgram.hpp>
#include <Engine/GBuffer.hpp>
#include <Engine/PerspCamera.hpp>
#include <Engine/DirLight.hpp>
#include <Engine/SpotLight.hpp>
#include <Engine/DepthMap.hpp>
#include <Engine/Texture2D.hpp>
#include <Engine/TextureCube.hpp>
#include <Engine/Material.hpp>

#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

inline std::string getDir(const GLchar *file)
{
	GLuint size, i;
	std::string path;

	for (size = i = 0; file[i] != '\0'; i++)
		if (file[i] == '/')
			size = i + 1;

	path.insert(0, file, 0, size);

	return path;
}

Engine::StaticModel::StaticModel(ShaderProgram *gProgram, ShaderProgram *smProgram)
	: Model(gProgram, smProgram)
{
	_matrixBuffer->createStore(GL_UNIFORM_BUFFER, NULL, sizeof _matrix, GL_DYNAMIC_DRAW);
}

Engine::StaticModel::StaticModel(StaticModel *model, ShaderProgram *gProgram, ShaderProgram *smProgram)
	: Model(model, gProgram, smProgram)
{
	_matrixBuffer->createStore(GL_UNIFORM_BUFFER, NULL, sizeof _matrix, GL_DYNAMIC_DRAW);
}

Engine::StaticModel::~StaticModel(void)
{
}

void Engine::StaticModel::loadFromFile(const GLchar *inFile)
{
	if (_isMirror == GL_TRUE)
	{
		std::cerr << "Error Model configuration" << std::endl;
		exit(1);
	}

	Assimp::Importer Importer;
	const aiScene *pScene = Importer.ReadFile(inFile, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace | aiProcess_JoinIdenticalVertices | aiProcess_OptimizeMeshes);
	if (!pScene)
	{
		std::string error = "Failed to load File: ";
		error.append(inFile);
		std::cout << error << std::endl;
		exit(1);
	}

	if (pScene->HasAnimations())
	{
		std::cerr << "The model is not static" << std::endl;
		exit(0);
	}

	std::vector<StaticMesh::Vertex> vertices;
	std::vector<GLuint> indices;
	for (GLuint i = 0; i < pScene->mNumMeshes; i++)
	{
		// Vertex Buffer
		for (GLuint j = 0; j < pScene->mMeshes[i]->mNumVertices; j++)
		{
			const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
			const aiVector3D pPos = pScene->mMeshes[i]->mVertices[j];
			const aiVector3D pTexCoord = pScene->mMeshes[i]->HasTextureCoords(0) ? pScene->mMeshes[i]->mTextureCoords[0][j] : Zero3D;
			const aiVector3D pNormal = pScene->mMeshes[i]->HasNormals() ? pScene->mMeshes[i]->mNormals[j] : Zero3D;
			const aiVector3D pTangent = pScene->mMeshes[i]->HasTangentsAndBitangents() ? pScene->mMeshes[i]->mTangents[j] : Zero3D;

			StaticMesh::Vertex newVertex = {
				{ pPos.x, pPos.y, pPos.z },
				{ pTexCoord.x, pTexCoord.y },
				{ pNormal.x, pNormal.y, pNormal.z },
				{ pTangent.x, pTangent.y, pTangent.z }
			};

			vertices.push_back(newVertex);
		}

		// Index Buffer
		for (GLuint j = 0; j < pScene->mMeshes[i]->mNumFaces; j++)
		{
			indices.push_back(pScene->mMeshes[i]->mFaces[j].mIndices[0]);
			indices.push_back(pScene->mMeshes[i]->mFaces[j].mIndices[1]);
			indices.push_back(pScene->mMeshes[i]->mFaces[j].mIndices[2]);
		}
		StaticMesh *newMesh = new StaticMesh;
		Material *newMaterial = new Material;

		_tObject->push_back(newMesh);
		_tObject->push_back(newMaterial);

		std::string dir = getDir(inFile);

		const aiTextureType _textureType[] = {
			aiTextureType_DIFFUSE, aiTextureType_SPECULAR,
			aiTextureType_AMBIENT, aiTextureType_EMISSIVE,
			aiTextureType_SHININESS, aiTextureType_OPACITY,
			aiTextureType_HEIGHT, aiTextureType_NORMALS,
			aiTextureType_DISPLACEMENT, aiTextureType_LIGHTMAP,
		};

		// Textures
		for (GLuint j = 0; j < (sizeof _textureType / sizeof *_textureType); j++)
		{
			aiString path;
			if (pScene->mMaterials[pScene->mMeshes[i]->mMaterialIndex]->GetTexture(_textureType[j], 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
			{
				std::string filePath = dir + path.C_Str();
				Texture2D *newTexture = new Texture2D;
				_tObject->push_back(newTexture);

				newTexture->loadFromFile(filePath.c_str());

				switch (_textureType[j])
				{
				case aiTextureType_DIFFUSE:
					newMaterial->setDiffuseTexture(newTexture);
					break;
				case aiTextureType_SPECULAR:
					newMaterial->setSpecularTexture(newTexture);
					break;
				case aiTextureType_AMBIENT:
					newMaterial->setAmbientTexture(newTexture);
					break;
				case aiTextureType_EMISSIVE:
					newMaterial->setEmissiveTexture(newTexture);
					break;
				case aiTextureType_SHININESS:
					newMaterial->setShininessTexture(newTexture);
					break;
				case aiTextureType_OPACITY:
					newMaterial->setOpacityTexture(newTexture);
					break;
				case aiTextureType_HEIGHT:
					newMaterial->setBumpMap(newTexture);
					break;
				case aiTextureType_NORMALS:
					newMaterial->setNormalMap(newTexture);
					break;
				case aiTextureType_DISPLACEMENT:
					newMaterial->setDisplacementMap(newTexture);
					break;
				case aiTextureType_LIGHTMAP:
					newMaterial->setLightMap(newTexture);
					break;
				default:
					break;
				}
			}
		}

	  {
		  aiColor4D mat;

		  pScene->mMaterials[pScene->mMeshes[i]->mMaterialIndex]->Get(AI_MATKEY_COLOR_DIFFUSE, mat);
		  newMaterial->setDiffuse(glm::vec3(mat.r, mat.g, mat.b));

		  pScene->mMaterials[pScene->mMeshes[i]->mMaterialIndex]->Get(AI_MATKEY_COLOR_SPECULAR, mat);
		  newMaterial->setSpecular(glm::vec3(mat.r, mat.g, mat.b));

		  pScene->mMaterials[pScene->mMeshes[i]->mMaterialIndex]->Get(AI_MATKEY_COLOR_AMBIENT, mat);
		  newMaterial->setAmbient(glm::vec3(mat.r, mat.g, mat.b));

		  pScene->mMaterials[pScene->mMeshes[i]->mMaterialIndex]->Get(AI_MATKEY_COLOR_EMISSIVE, mat);
		  newMaterial->setEmissive(glm::vec3(mat.r, mat.g, mat.b));

		  pScene->mMaterials[pScene->mMeshes[i]->mMaterialIndex]->Get(AI_MATKEY_SHININESS, mat);
		  newMaterial->setShininess(mat.r);

		  pScene->mMaterials[pScene->mMeshes[i]->mMaterialIndex]->Get(AI_MATKEY_OPACITY, mat);
		  newMaterial->setOpacity(mat.r);
	  }

	  newMesh->setMaterial(newMaterial);
	  newMesh->load((GLsizei)vertices.size(), vertices.data(), (GLsizei)indices.size(), indices.data());

	  addMesh(newMesh);

	  vertices.clear();
	  indices.clear();
	}
}

void Engine::StaticModel::display(GBuffer *gbuf, PerspCamera *cam)
{
	checkMatrix();

	gbuf->setGeometryState();

	glUseProgram(_gProgram->getId());

	_matrix.MVP = cam->getVPMatrix() * *_modelMatrix;
	_matrix.projection = cam->getProjectionMatrix();
	_matrix.view = cam->getViewMatrix();
	_matrix.model = *_modelMatrix;
	_matrix.normal = *_normalMatrix;
	_matrixBuffer->updateStoreMap(&_matrix);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, _matrixBuffer->getId());

	_camera.position = cam->getCameraPosition();
	_camera.forward = cam->getForwardVector();
	_camera.left = cam->getLeftVector();
	_camera.up = cam->getUpVector();
	_cameraBuffer->updateStoreMap(&_camera);
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, _cameraBuffer->getId());

	for (GLuint i = 0; i < _tMesh->size(); i++)
		if ((*_tMesh)[i]->getMaterial()->getOpacity() == 1.0f)
		{
			if (_cubeTexture)
				(*_tMesh)[i]->display(_cubeTexture);
			else
				(*_tMesh)[i]->display();
		}
}

void Engine::StaticModel::displayTransparent(GBuffer *gbuf, PerspCamera *cam)
{
	checkMatrix();

	gbuf->setGeometryState();

	glUseProgram(_gProgram->getId());

	_matrix.MVP = cam->getVPMatrix() * *_modelMatrix;
	_matrix.projection = cam->getProjectionMatrix();
	_matrix.view = cam->getViewMatrix();
	_matrix.model = *_modelMatrix;
	_matrix.normal = *_normalMatrix;
	_matrixBuffer->updateStoreMap(&_matrix);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, _matrixBuffer->getId());

	_camera.position = cam->getCameraPosition();
	_camera.forward = cam->getForwardVector();
	_camera.left = cam->getLeftVector();
	_camera.up = cam->getUpVector();
	_cameraBuffer->updateStoreMap(&_camera);
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, _cameraBuffer->getId());

	for (GLuint i = 0; i < _tMesh->size(); i++)
		if ((*_tMesh)[i]->getMaterial()->getOpacity() < 1.0f)
		{
			if (_cubeTexture)
				(*_tMesh)[i]->display(_cubeTexture);
			else
				(*_tMesh)[i]->display();
		}
}

void Engine::StaticModel::displayDepthMap(DepthMap *dmap, Camera *cam)
{
	checkMatrix();

	dmap->setState();

	glUseProgram(_smProgram->getId());

	_matrix.MVP = cam->getVPMatrix() * *_modelMatrix;
	_matrix.projection = cam->getProjectionMatrix();
	_matrix.view = cam->getViewMatrix();
	_matrix.model = *_modelMatrix;
	_matrix.normal = *_normalMatrix;
	_matrixBuffer->updateStoreMap(&_matrix);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, _matrixBuffer->getId());

	for (GLuint i = 0; i < _tMesh->size(); i++)
		if ((*_tMesh)[i]->getMaterial()->getOpacity() == 1.0f)
			(*_tMesh)[i]->displayShadow();
}

void Engine::StaticModel::displayDepthMap(DepthMap *dmaps, DirLight *light)
{
	checkMatrix();

	glUseProgram(_smProgram->getId());

	_matrix.model = *_modelMatrix;
	_matrix.normal = *_normalMatrix;

	for (GLuint i = 0; i < CSM_NUM; i++)
	{
		dmaps[i].setState();

		_matrix.MVP = light->getVPMatrix(i) * *_modelMatrix;
		_matrix.projection = light->getProjectionMatrix(i);
		_matrix.view = light->getViewMatrix(i);

		_matrixBuffer->updateStoreMap(&_matrix);
		glBindBufferBase(GL_UNIFORM_BUFFER, 0, _matrixBuffer->getId());

		for (GLuint j = 0; j < _tMesh->size(); j++)
			if ((*_tMesh)[j]->getMaterial()->getOpacity() == 1.0f)
				(*_tMesh)[j]->displayShadow();
	}
}

void Engine::StaticModel::displayDepthMap(DepthMap *dmap, SpotLight *light)
{
	checkMatrix();

	dmap->setState();

	glUseProgram(_smProgram->getId());

	_matrix.MVP = light->getVPMatrix() * *_modelMatrix;
	_matrix.projection = light->getProjectionMatrix();
	_matrix.view = light->getViewMatrix();
	_matrix.model = *_modelMatrix;
	_matrix.normal = *_normalMatrix;
	_matrixBuffer->updateStoreMap(&_matrix);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, _matrixBuffer->getId());

	for (GLuint i = 0; i < _tMesh->size(); i++)
		if ((*_tMesh)[i]->getMaterial()->getOpacity() == 1.0f)
			(*_tMesh)[i]->displayShadow();
}