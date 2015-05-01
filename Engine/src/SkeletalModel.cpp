#include <Engine/SkeletalModel.hpp>
#include <Engine/SkeletalMesh.hpp>
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

#include "tools/AssimpTool.hpp"

Engine::SkeletalModel::SkeletalModel(ShaderProgram *gProgram, ShaderProgram *smProgram)
	: Model(gProgram, smProgram)
{
	_offsetMatrices = new std::vector < glm::mat4 > ;

	_matrixBuffer->createStore(GL_UNIFORM_BUFFER, NULL, sizeof _matrix, GL_DYNAMIC_DRAW);
}

Engine::SkeletalModel::SkeletalModel(SkeletalModel *model, ShaderProgram *gProgram, ShaderProgram *smProgram)
	: Model(model, gProgram, smProgram)
{
	_offsetMatrices = new std::vector < glm::mat4 >;

	*_offsetMatrices = *model->_offsetMatrices;

	_matrixBuffer->createStore(GL_UNIFORM_BUFFER, NULL, sizeof _matrix, GL_DYNAMIC_DRAW);
}

Engine::SkeletalModel::~SkeletalModel(void)
{
	delete _offsetMatrices;
}

void Engine::SkeletalModel::loadFromFile(const GLchar *inFile, const GLchar *node_name)
{
	if (_isMirror == GL_TRUE)
	{
		std::cerr << "Error Model configuration" << std::endl;
		abort();
	}

	_tMesh->clear();

	Assimp::Importer importer;
	const aiScene *pScene = AssimpTool::openFile(importer, inFile);
	if (!pScene->HasAnimations())
	{
		std::cerr << "The model is not animated" << std::endl;
		abort();
	}

	GLuint bone_index = 0;
	std::map<GLuint, GLuint> map_vertex;
	std::vector<glm::mat4> tmp_vector;

	std::pair<std::vector<SkeletalMesh::Vertex>, std::vector<GLuint>> vertices_index;
	Material *material;
	SkeletalMesh *mesh;
	for (GLuint i = 0; i < pScene->mNumMeshes; i++)
	{
		vertices_index = AssimpTool::loadSkeletalVertices(pScene->mMeshes[i], map_vertex);
		material = AssimpTool::loadMaterial(pScene->mMaterials[pScene->mMeshes[i]->mMaterialIndex], getDir(inFile), _tObject);
		tmp_vector = AssimpTool::loadBones(pScene->mMeshes[i], bone_index, vertices_index.first, map_vertex);

		_offsetMatrices->insert(_offsetMatrices->end(), tmp_vector.begin(), tmp_vector.end());

		mesh = new SkeletalMesh;
		_tObject->insert(mesh);

		mesh->setMaterial(material);
		mesh->load(vertices_index.first, vertices_index.second);

		vertices_index.first.clear();
		vertices_index.second.clear();

		addMesh(mesh);
	}

	try
	{
		_skeleton = AssimpTool::loadSkeleton(pScene, node_name);
	}
	catch (std::exception exception)
	{
		std::cerr << inFile << " No node " << node_name << std::endl;
		abort();
	}
}

void Engine::SkeletalModel::display(GBuffer *gbuf, PerspCamera *cam)
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

void Engine::SkeletalModel::displayTransparent(GBuffer *gbuf, PerspCamera *cam)
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

void Engine::SkeletalModel::displayDepthMap(DepthMap *dmap, Camera *cam)
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

void Engine::SkeletalModel::displayDepthMap(DepthMap *dmaps, DirLight *light)
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

void Engine::SkeletalModel::displayDepthMap(DepthMap *dmap, SpotLight *light)
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