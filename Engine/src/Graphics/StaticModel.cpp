#include <Engine/Graphics/StaticModel.hpp>

#include "../Tools/private/AssimpTool.hpp"

Engine::StaticModel::StaticModel(const std::shared_ptr<ShaderProgram> &gProgram, const std::shared_ptr<ShaderProgram> &smProgram)
	: Model(gProgram, smProgram)
{
	_matrixBuffer->createStore(GL_UNIFORM_BUFFER, NULL, sizeof _matrix, GL_DYNAMIC_DRAW);
}

Engine::StaticModel::StaticModel(const std::shared_ptr<StaticModel> &model, const std::shared_ptr<ShaderProgram> &gProgram, const std::shared_ptr<ShaderProgram> &smProgram)
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
		abort();
	}

	_tMesh->clear();

	Assimp::Importer importer;
	const aiScene *pScene = AssimpTool::openFile(importer, inFile);
	if (pScene->HasAnimations())
	{
		std::cerr << "The model is not static" << std::endl;
		abort();
	}

	std::vector<StaticMesh::Vertex> vertices;
	std::vector<GLuint> indices;
	for (GLuint i = 0; i < pScene->mNumMeshes; i++)
	{
		std::shared_ptr<StaticMesh> mesh = std::shared_ptr<StaticMesh>(new StaticMesh);

		vertices = AssimpTool::loadStaticVertices(pScene->mMeshes[i]);
		indices = AssimpTool::loadIndices(pScene->mMeshes[i]);
		mesh->setMaterial(AssimpTool::loadMaterial(pScene->mMaterials[pScene->mMeshes[i]->mMaterialIndex], getDir(inFile)));
		
		mesh->load(vertices, indices);

		vertices.clear();
		indices.clear();

		addMesh(mesh);
	}
}

void Engine::StaticModel::display(const std::shared_ptr<GBuffer> &gbuf, const std::shared_ptr<PerspCamera> &cam)
{
	checkMatrix();

	gbuf->setGeometryState();

	glUseProgram(_gProgram->getId());

	_matrix.MVP = cam->getVPMatrix() * _modelMatrix;
	_matrix.projection = cam->getProjectionMatrix();
	_matrix.view = cam->getViewMatrix();
	_matrix.model = _modelMatrix;
	_matrix.normal = _normalMatrix;
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

void Engine::StaticModel::displayTransparent(const std::shared_ptr<GBuffer> &gbuf, const std::shared_ptr<PerspCamera> &cam)
{
	checkMatrix();

	gbuf->setGeometryState();

	glUseProgram(_gProgram->getId());

	_matrix.MVP = cam->getVPMatrix() * _modelMatrix;
	_matrix.projection = cam->getProjectionMatrix();
	_matrix.view = cam->getViewMatrix();
	_matrix.model = _modelMatrix;
	_matrix.normal = _normalMatrix;
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

void Engine::StaticModel::displayDepthMap(const std::shared_ptr<DepthMap> &depthMap, const std::shared_ptr<Camera> &cam)
{
	checkMatrix();

	depthMap->setState();

	glUseProgram(_smProgram->getId());

	_matrix.MVP = cam->getVPMatrix() * _modelMatrix;
	_matrix.projection = cam->getProjectionMatrix();
	_matrix.view = cam->getViewMatrix();
	_matrix.model = _modelMatrix;
	_matrix.normal = _normalMatrix;
	_matrixBuffer->updateStoreMap(&_matrix);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, _matrixBuffer->getId());

	for (GLuint i = 0; i < _tMesh->size(); i++)
		if ((*_tMesh)[i]->getMaterial()->getOpacity() == 1.0f)
			(*_tMesh)[i]->displayShadow();
}

void Engine::StaticModel::displayDepthMap(const std::shared_ptr<DepthMap> &depthMap, const std::shared_ptr<SpotLight> &light)
{
	checkMatrix();

	depthMap->setState();

	glUseProgram(_smProgram->getId());

	_matrix.MVP = light->getVPMatrix() * _modelMatrix;
	_matrix.projection = light->getProjectionMatrix();
	_matrix.view = light->getViewMatrix();
	_matrix.model = _modelMatrix;
	_matrix.normal = _normalMatrix;
	_matrixBuffer->updateStoreMap(&_matrix);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, _matrixBuffer->getId());

	for (GLuint i = 0; i < _tMesh->size(); i++)
		if ((*_tMesh)[i]->getMaterial()->getOpacity() == 1.0f)
			(*_tMesh)[i]->displayShadow();
}

void Engine::StaticModel::displayDepthMaps(const std::vector<std::shared_ptr<DepthMap>> &depthMaps, const std::shared_ptr<DirLight> &light)
{
	if (depthMaps.size() != CSM_NUM)
	{
		std::cerr << "Wrong vector of depthMap size" << std::endl;
		abort();
	}

	checkMatrix();

	glUseProgram(_smProgram->getId());

	_matrix.model = _modelMatrix;
	_matrix.normal = _normalMatrix;

	for (GLuint i = 0; i < CSM_NUM; i++)
	{
		depthMaps[i]->setState();

		_matrix.MVP = light->getVPMatrix(i) * _modelMatrix;
		_matrix.projection = light->getProjectionMatrix(i);
		_matrix.view = light->getViewMatrix(i);

		_matrixBuffer->updateStoreMap(&_matrix);
		glBindBufferBase(GL_UNIFORM_BUFFER, 0, _matrixBuffer->getId());

		for (GLuint j = 0; j < _tMesh->size(); j++)
			if ((*_tMesh)[j]->getMaterial()->getOpacity() == 1.0f)
				(*_tMesh)[j]->displayShadow();
	}
}