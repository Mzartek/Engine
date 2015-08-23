#include <Engine/Graphics/SkeletalModel.hpp>

#include "../Tools/private/AssimpTool.hpp"

Engine::Graphics::SkeletalModel::SkeletalModel(const std::shared_ptr<ShaderProgram> &gProgram, const std::shared_ptr<ShaderProgram> &smProgram)
	: Model(gProgram, smProgram)
{
	_matrixBuffer->createStore(GL_UNIFORM_BUFFER, NULL, sizeof _matrix, GL_DYNAMIC_DRAW);
}

Engine::Graphics::SkeletalModel::SkeletalModel(const std::shared_ptr<SkeletalModel> &model, const std::shared_ptr<ShaderProgram> &gProgram, const std::shared_ptr<ShaderProgram> &smProgram)
	: Model(model, gProgram, smProgram)
{
	_bones = model->_bones;

	_matrixBuffer->createStore(GL_UNIFORM_BUFFER, NULL, sizeof _matrix, GL_DYNAMIC_DRAW);
}

Engine::Graphics::SkeletalModel::~SkeletalModel(void)
{
}

void Engine::Graphics::SkeletalModel::loadFromFile(const GLchar *inFile, const GLchar *node_name)
{
	if (_isMirror == GL_TRUE)
	{
		throw std::exception("Error Model configuration");
	}

	_tMesh->clear();

	Assimp::Importer importer;
	const aiScene *pScene = ToolsPrivate::openFile(importer, inFile);
	if (!pScene->HasAnimations())
	{
		throw std::exception("The model is not animated");
	}

	try
	{
		_skeleton = ToolsPrivate::loadSkeleton(pScene, node_name);
	}
	catch (std::exception exception)
	{
		throw std::exception(std::string(inFile + std::string(" No node ") + node_name).c_str());
	}

	GLuint bone_index = 0;
	std::map<GLuint, GLuint> map_vertex;
	std::vector<SkeletalMesh::Vertex> vertices;
	std::vector<GLuint> indices;
	for (GLuint i = 0; i < pScene->mNumMeshes; i++)
	{
		std::shared_ptr<SkeletalMesh> mesh = std::shared_ptr<SkeletalMesh>(new SkeletalMesh);

		vertices = ToolsPrivate::loadSkeletalVertices(pScene->mMeshes[i], map_vertex);
		indices = ToolsPrivate::loadIndices(pScene->mMeshes[i]);
		mesh->setMaterial(ToolsPrivate::loadMaterial(pScene->mMaterials[pScene->mMeshes[i]->mMaterialIndex], Tools::getDir(inFile)));

		std::vector<std::shared_ptr<Engine::Graphics::Bone>> tmp_vector = ToolsPrivate::loadBones(pScene->mMeshes[i], _skeleton, bone_index, vertices, map_vertex);
		_bones.insert(_bones.end(), tmp_vector.begin(), tmp_vector.end());

		mesh->load(vertices, indices);

		vertices.clear();
		indices.clear();

		addMesh(mesh);
	}
}

void Engine::Graphics::SkeletalModel::display(const std::shared_ptr<GBuffer> &gbuf, const std::shared_ptr<PerspCamera> &cam)
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
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, cam->getCameraInfoBuffer()->getId());

	for (GLuint i = 0; i < _tMesh->size(); i++)
		if ((*_tMesh)[i]->getMaterial()->getOpacity() == 1.0f)
		{
			if (_cubeTexture)
				(*_tMesh)[i]->display(_cubeTexture);
			else
				(*_tMesh)[i]->display();
		}
}

void Engine::Graphics::SkeletalModel::displayTransparent(const std::shared_ptr<GBuffer> &gbuf, const std::shared_ptr<PerspCamera> &cam)
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
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, cam->getCameraInfoBuffer()->getId());

	for (GLuint i = 0; i < _tMesh->size(); i++)
		if ((*_tMesh)[i]->getMaterial()->getOpacity() < 1.0f)
		{
			if (_cubeTexture)
				(*_tMesh)[i]->display(_cubeTexture);
			else
				(*_tMesh)[i]->display();
		}
}

void Engine::Graphics::SkeletalModel::displayDepthMap(const std::shared_ptr<DepthMap> &depthMap, const std::shared_ptr<Camera> &cam)
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

void Engine::Graphics::SkeletalModel::displayDepthMap(const std::shared_ptr<DepthMap> &depthMap, const std::shared_ptr<SpotLight> &light)
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

void Engine::Graphics::SkeletalModel::displayDepthMaps(const std::vector<std::shared_ptr<DepthMap>> &depthMaps, const std::shared_ptr<DirLight> &light)
{
	if (depthMaps.size() != DirLight::CASCADED_LEVEL)
	{
		throw std::invalid_argument("Wrong vector of depthMap size");
	}

	checkMatrix();

	glUseProgram(_smProgram->getId());

	_matrix.model = _modelMatrix;
	_matrix.normal = _normalMatrix;

	for (GLuint i = 0; i < DirLight::CASCADED_LEVEL; i++)
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