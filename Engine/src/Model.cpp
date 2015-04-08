#include <Engine/Model.hpp>
#include <Engine/Mesh.hpp>
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

void Engine::Model::genMatModel(void) const
{
	*_modelMatrix = glm::translate(*_position) *
		glm::rotate(_rotation->x, glm::vec3(1, 0, 0)) *
		glm::rotate(_rotation->y, glm::vec3(0, 1, 0)) *
		glm::rotate(_rotation->z, glm::vec3(0, 0, 1)) *
		glm::scale(*_scale);
}

void Engine::Model::genMatNormal(void) const
{
	*_normalMatrix = glm::transpose(glm::inverse(*_modelMatrix));
}

void Engine::Model::checkMatrix(void)
{
	if (_needMatModel == GL_TRUE)
	{
		genMatModel();
		_needMatModel = GL_FALSE;
	}
	if (_needMatNormal == GL_TRUE)
	{
		genMatNormal();
		_needMatNormal = GL_FALSE;
	}
}

Engine::Model::Model(ShaderProgram *gProgram, ShaderProgram *smProgram)
	: _isMirror(GL_FALSE), _needMatModel(GL_TRUE), _needMatNormal(GL_TRUE), _cubeTexture(NULL), _gProgram(gProgram), _smProgram(smProgram)
{
	_tMesh = new std::vector < Mesh * > ;
	_tObject = new std::vector < Object * > ;
	_matrixBuffer = new Buffer;
	_cameraBuffer = new Buffer;
	_position = new glm::vec3;
	_rotation = new glm::vec3;
	_scale = new glm::vec3;
	_modelMatrix = new glm::mat4;
	_normalMatrix = new glm::mat4;

	*_position = glm::vec3(0, 0, 0);
	*_rotation = glm::vec3(0, 0, 0);
	*_scale = glm::vec3(1, 1, 1);

	_matrixBuffer->createStore(GL_UNIFORM_BUFFER, NULL, sizeof _matrix, GL_DYNAMIC_DRAW);
	_cameraBuffer->createStore(GL_UNIFORM_BUFFER, NULL, sizeof _camera, GL_DYNAMIC_DRAW);

	glUseProgram(_gProgram->getId());
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "diffuseTex"), 0);
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "specularTex"), 1);
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "ambiantTex"), 2);
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "emissiveTex"), 3);
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "shininessTex"), 4);
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "opacityTex"), 5);
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "bumpMap"), 6);
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "normalMap"), 7);
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "displacementMap"), 8);
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "lightMap"), 9);
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "reflectionTex"), 10);
	glUseProgram(_smProgram->getId());
	glUniform1i(glGetUniformLocation(_smProgram->getId(), "diffuseTex"), 0);
}

Engine::Model::Model(Model *model, ShaderProgram *gProgram, ShaderProgram *smProgram)
	: _isMirror(GL_TRUE), _needMatModel(GL_TRUE), _needMatNormal(GL_TRUE), _cubeTexture(NULL), _gProgram(gProgram), _smProgram(smProgram)
{
	_tMesh = model->_tMesh;
	_tObject = new std::vector < Object * > ;
	_matrixBuffer = new Buffer;
	_cameraBuffer = new Buffer;
	_position = new glm::vec3;
	_rotation = new glm::vec3;
	_scale = new glm::vec3;
	_modelMatrix = new glm::mat4;
	_normalMatrix = new glm::mat4;

	*_position = glm::vec3(0, 0, 0);
	*_rotation = glm::vec3(0, 0, 0);
	*_scale = glm::vec3(1, 1, 1);

	_matrixBuffer->createStore(GL_UNIFORM_BUFFER, NULL, sizeof _matrix, GL_DYNAMIC_DRAW);
	_cameraBuffer->createStore(GL_UNIFORM_BUFFER, NULL, sizeof _camera, GL_DYNAMIC_DRAW);

	glUseProgram(_gProgram->getId());
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "diffuseTex"), 0);
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "specularTex"), 1);
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "ambiantTex"), 2);
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "emissiveTex"), 3);
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "shininessTex"), 4);
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "opacityTex"), 5);
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "bumpMap"), 6);
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "normalMap"), 7);
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "displacementMap"), 8);
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "lightMap"), 9);
	glUseProgram(_smProgram->getId());
	glUniform1i(glGetUniformLocation(_smProgram->getId(), "diffuseTex"), 0);
}

Engine::Model::~Model(void)
{
	if (!_isMirror) delete _tMesh;

	for (std::vector<Object *>::iterator it = _tObject->begin(); it != _tObject->end(); it++)
		delete *it;
	delete _tObject;

	delete _matrixBuffer;
	delete _cameraBuffer;
	delete _position;
	delete _rotation;
	delete _scale;
	delete _modelMatrix;
	delete _normalMatrix;
}

void Engine::Model::addMesh(Mesh *mesh)
{
	if (_isMirror == GL_TRUE)
	{
		std::cerr << "Error Model configuration" << std::endl;
		exit(1);
	}

	_tMesh->push_back(mesh);
}

void Engine::Model::loadFromFile(const GLchar *inFile)
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

	std::vector<Vertex> vertices;
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

			Vertex newVertex = {
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
		Mesh *newMesh = new Mesh;
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

void Engine::Model::sortMesh(void)
{
	std::sort(_tMesh->begin(), _tMesh->end(), CompareMesh());
}

void Engine::Model::setPosition(const glm::vec3 &position)
{
	*_position = position;
	_needMatModel = GL_TRUE;
}

void Engine::Model::setRotation(const glm::vec3 &rotation)
{
	*_rotation = rotation;
	_needMatModel = GL_TRUE;
	_needMatNormal = GL_TRUE;
}

void Engine::Model::setScale(const glm::vec3 &scale)
{
	*_scale = scale;
	_needMatModel = GL_TRUE;
	_needMatNormal = GL_TRUE;
}

void Engine::Model::setCubeTexture(TextureCube *cubeTexture)
{
	_cubeTexture = cubeTexture;
}

glm::vec3 Engine::Model::getPosition(void) const
{
	return *_position;
}

glm::vec3 Engine::Model::getRotation(void) const
{
	return *_rotation;
}

glm::vec3 Engine::Model::getScale(void) const
{
	return *_scale;
}

Engine::Mesh *Engine::Model::getMesh(const GLuint &num) const
{
	if (num >= _tMesh->size())
	{
		std::cerr << "Bad num Mesh" << std::endl;
		return NULL;
	}
	return (*_tMesh)[num];
}

void Engine::Model::display(GBuffer *gbuf, PerspCamera *cam)
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
	_camera.target = cam->getTargetPosition();
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

void Engine::Model::displayTransparent(GBuffer *gbuf, PerspCamera *cam)
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
	_camera.target = cam->getTargetPosition();
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

void Engine::Model::displayDepthMap(DepthMap *dmap, Camera *cam)
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

void Engine::Model::displayDepthMap(DepthMap *dmaps, DirLight *light)
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

void Engine::Model::displayDepthMap(DepthMap *dmap, SpotLight *light)
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
