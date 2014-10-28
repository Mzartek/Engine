#include <Engine/Model.hpp>
#include <Engine/Mesh.hpp>
#include <Engine/Buffer.hpp>
#include <Engine/ShaderProgram.hpp>
#include <Engine/GBuffer.hpp>
#include <Engine/Camera.hpp>
#include <Engine/Light.hpp>
#include <Engine/ShadowMap.hpp>

#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

Engine::Model::Model(ShaderProgram *gProgram, ShaderProgram *smProgram)
	: _tMesh(NULL)
{
	_MVPMatrixBuffer = new Buffer;
	_normalMatrixBuffer = new Buffer;
	_modelMatrix = new glm::mat4;

	_MVPMatrixBuffer->createStore(GL_UNIFORM_BUFFER, NULL, sizeof(glm::mat4), GL_DYNAMIC_DRAW);
	_normalMatrixBuffer->createStore(GL_UNIFORM_BUFFER, NULL, sizeof(glm::mat4), GL_DYNAMIC_DRAW);

	_gProgram = gProgram;
	_smProgram = smProgram;
	glUseProgram(_gProgram->getId());
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "colorTexture"), 0);
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "NMTexture"), 1);
	glUseProgram(_smProgram->getId());
	glUniform1i(glGetUniformLocation(_smProgram->getId(), "colorTexture"), 0);
}

Engine::Model::~Model(void)
{
	GLuint i;
	if (_tMesh != NULL && isMirror != GL_TRUE)
	{
		for (i = 0; i<_tMesh->size(); i++)
			delete (*_tMesh)[i];
		delete _tMesh;
	}
	delete _MVPMatrixBuffer;
	delete _normalMatrixBuffer;
	delete _modelMatrix;
}

void Engine::Model::initMeshArray(void)
{
	GLuint i;
	if (_tMesh != NULL && isMirror != GL_TRUE)
	{
		for (i = 0; i<_tMesh->size(); i++)
			delete (*_tMesh)[i];
		delete _tMesh;
	}
	isMirror = GL_FALSE;
	_tMesh = new std::vector<Mesh *>;
}

void Engine::Model::initMeshMirror(Model *m)
{
	GLuint i;
	if (_tMesh != NULL && isMirror != GL_TRUE)
	{
		for (i = 0; i<_tMesh->size(); i++)
			delete (*_tMesh)[i];
		delete _tMesh;
	}
	isMirror = GL_TRUE;
	_tMesh = m->_tMesh;
}

void Engine::Model::addMesh(const GLsizei &sizeVertexArray, const GLfloat *vertexArray,
				 const GLsizei &sizeIndexArray, const GLuint *indexArray,
				 const GLchar *colorTexture, const GLchar *NMTexture,
				 const glm::vec4 &ambient, const glm::vec4 &diffuse, const glm::vec4 &specular, const GLfloat &shininess)
{
	Mesh *newone = new Mesh;

	newone->setColorTexture(colorTexture);
	newone->setNMTexture(NMTexture);
	newone->setAmbient(ambient);
	newone->setDiffuse(diffuse);
	newone->setSpecular(specular);
	newone->setShininess(shininess);
	newone->load(sizeVertexArray, vertexArray,
		     sizeIndexArray, indexArray);

	_tMesh->push_back(newone);
}

static std::string getDir(const GLchar *file)
{
	GLuint size, i;
	std::string path;

	for (size = i = 0; file[i] != '\0'; i++)
		if (file[i] == '/')
			size = i + 1;

	path.insert(0, file, 0, size);

	return path;
}

void Engine::Model::loadFromFile(const GLchar *file)
{
	Assimp::Importer Importer;
	GLuint i, j;

	if (_tMesh == NULL || isMirror == GL_TRUE)
	{
		std::cerr << "Error Model configuration" << std::endl;
		exit(1);
	}
	for (i = 0; i<_tMesh->size(); i++)
		delete (*_tMesh)[i];
	_tMesh->clear();

	const aiScene *pScene = Importer.ReadFile(file, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace | aiProcess_JoinIdenticalVertices | aiProcess_OptimizeMeshes);
	if (!pScene)
	{
		std::cerr << "Unable to load the model: " << file << std::endl;
		exit(1);
	}

	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;
	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
	const aiVector3D *pPos;
	const aiVector3D *pTexCoord;
	const aiVector3D *pNormal;
	const aiVector3D *pTangent;
	for (i = 0; i<pScene->mNumMeshes; i++)
	{
		// Vertex Buffer
		for (j = 0; j<pScene->mMeshes[i]->mNumVertices; j++)
		{
			pPos = &(pScene->mMeshes[i]->mVertices[j]);
			pTexCoord = pScene->mMeshes[i]->HasTextureCoords(0) ? &(pScene->mMeshes[i]->mTextureCoords[0][j]) : &Zero3D;
			pNormal = pScene->mMeshes[i]->HasNormals() ? &(pScene->mMeshes[i]->mNormals[j]) : &Zero3D;
			pTangent = pScene->mMeshes[i]->HasTangentsAndBitangents() ? &(pScene->mMeshes[i]->mTangents[j]) : &Zero3D;

			vertices.push_back(pPos->x), vertices.push_back(pPos->y), vertices.push_back(pPos->z);
			vertices.push_back(pTexCoord->x), vertices.push_back(pTexCoord->y);
			vertices.push_back(pNormal->x), vertices.push_back(pNormal->y), vertices.push_back(pNormal->z);
			vertices.push_back(pTangent->x), vertices.push_back(pTangent->y), vertices.push_back(pTangent->z);
		}

		// Index Buffer
		for (j = 0; j < pScene->mMeshes[i]->mNumFaces; j++)
		{
			indices.push_back(pScene->mMeshes[i]->mFaces[j].mIndices[0]);
			indices.push_back(pScene->mMeshes[i]->mFaces[j].mIndices[1]);
			indices.push_back(pScene->mMeshes[i]->mFaces[j].mIndices[2]);
		}

		aiString path;
		std::string dir, colorPath, NMPath;
		dir = getDir(file);
		if (pScene->mMaterials[pScene->mMeshes[i]->mMaterialIndex]->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
			colorPath += dir + path.C_Str();
		else
			colorPath = "resources/none.png";
		if (pScene->mMaterials[pScene->mMeshes[i]->mMaterialIndex]->GetTexture(aiTextureType_NORMALS, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
			NMPath += dir + "NM_" + path.C_Str();
		else
			NMPath = "resources/NM_none.png";

		aiColor4D mat_ambient;
		aiColor4D mat_diffuse;
		aiColor4D mat_specular;
		GLfloat mat_shininess;
		GLfloat opacity;

		pScene->mMaterials[pScene->mMeshes[i]->mMaterialIndex]->Get(AI_MATKEY_COLOR_AMBIENT, mat_ambient);
		pScene->mMaterials[pScene->mMeshes[i]->mMaterialIndex]->Get(AI_MATKEY_COLOR_DIFFUSE, mat_diffuse);
		pScene->mMaterials[pScene->mMeshes[i]->mMaterialIndex]->Get(AI_MATKEY_COLOR_SPECULAR, mat_specular);
		pScene->mMaterials[pScene->mMeshes[i]->mMaterialIndex]->Get(AI_MATKEY_SHININESS, mat_shininess);
		pScene->mMaterials[pScene->mMeshes[i]->mMaterialIndex]->Get(AI_MATKEY_OPACITY, opacity);
		mat_ambient.a = opacity;
		mat_diffuse.a = opacity;
		mat_specular.a = opacity;

		this->addMesh((GLsizei)vertices.size() * sizeof(GLfloat), &vertices[0],
			(GLsizei)indices.size() * sizeof(GLuint), &indices[0],
			colorPath.c_str(), NMPath.c_str(),
			glm::vec4(mat_ambient.r, mat_ambient.g, mat_ambient.b, mat_ambient.a), glm::vec4(mat_diffuse.r, mat_diffuse.g, mat_diffuse.b, mat_diffuse.a), glm::vec4(mat_specular.r, mat_specular.g, mat_specular.b, mat_specular.a),
			mat_shininess);

		vertices.clear();
		indices.clear();
	}
}

void Engine::Model::sortMesh(void)
{
	qsort(&(*_tMesh)[0], _tMesh->size(), sizeof (*_tMesh)[0], comparMesh);
}

void Engine::Model::matIdentity(void)
{
	*_modelMatrix = glm::mat4(1.0f);
}

void Engine::Model::matTranslate(const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
	*_modelMatrix *= glm::translate(glm::vec3(x, y, z));
}

void Engine::Model::matRotate(const GLfloat &angle, const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
	*_modelMatrix *= glm::rotate(angle * (glm::pi<GLfloat>() / 180), glm::vec3(x, y, z));
}

void Engine::Model::matScale(const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
	*_modelMatrix *= glm::scale(glm::vec3(x, y, z));
}

glm::vec3 Engine::Model::getPosition(void) const
{
	return glm::vec3((*_modelMatrix)[3][0], (*_modelMatrix)[3][1], (*_modelMatrix)[3][2]);
}

Engine::Mesh *Engine::Model::getMesh(const GLuint &num) const
{
	if(num>=_tMesh->size())
	{
		std::cerr << "Bad num Mesh" << std::endl;
		return NULL;
	}
	return (*_tMesh)[num];
}

void Engine::Model::display(GBuffer *gbuf, Camera *cam) const
{
	GLuint i;

	gbuf->setGeometryState();

	glUseProgram(_gProgram->getId());

	_MVPMatrixBuffer->updateStoreMap(glm::value_ptr(cam->getVPMatrix() * *_modelMatrix));
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, _MVPMatrixBuffer->getId());
	_normalMatrixBuffer->updateStoreMap(glm::value_ptr(glm::transpose(glm::inverse(*_modelMatrix))));
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, _normalMatrixBuffer->getId());

	for(i=0 ; i<_tMesh->size(); i++)
        if((*_tMesh)[i]->getTransparency() == 1.0f)
			(*_tMesh)[i]->display();
}

void Engine::Model::displayTransparent(GBuffer *gbuf, Camera *cam) const
{
	GLuint i;

	gbuf->setGeometryState();

	glUseProgram(_gProgram->getId());

	_MVPMatrixBuffer->updateStoreMap(glm::value_ptr(cam->getVPMatrix() * *_modelMatrix));
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, _MVPMatrixBuffer->getId());
	_normalMatrixBuffer->updateStoreMap(glm::value_ptr(glm::transpose(glm::inverse(*_modelMatrix))));
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, _normalMatrixBuffer->getId());

	for (i = 0; i<_tMesh->size(); i++)
		if ((*_tMesh)[i]->getTransparency() != 1.0f)
			(*_tMesh)[i]->display();
}

void Engine::Model::displayShadowMap(Light *light) const
{
	GLuint i;

	light->getShadowMap()->setState();

	glUseProgram(_smProgram->getId());

	_MVPMatrixBuffer->updateStoreMap(glm::value_ptr(light->getVPMatrix() * *_modelMatrix));
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, _MVPMatrixBuffer->getId());

	for(i=0 ; i<_tMesh->size(); i++)
        if((*_tMesh)[i]->getTransparency() == 1.0f)
			(*_tMesh)[i]->displayShadow();
}
