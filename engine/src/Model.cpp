#include <Engine/Model.hpp>
#include <Engine/Mesh.hpp>
#include <Engine/ShaderProgram.hpp>
#include <Engine/GBuffer.hpp>
#include <Engine/Camera.hpp>
#include <Engine/Light.hpp>
#include <Engine/ShadowMap.hpp>

#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

engine::Model::Model(void)
	: _tMesh(NULL)
{
	_modelMatrix = new glm::mat4;
}

engine::Model::~Model(void)
{
	GLuint i;
	if (_tMesh != NULL && isMirror == GL_FALSE)
	{
		for (i = 0; i<_tMesh->size(); i++)
			delete (*_tMesh)[i];
		delete _tMesh;
	}
	delete _modelMatrix;
}

void engine::Model::initMeshArray(void)
{
	GLuint i;
	if (_tMesh != NULL && isMirror == GL_FALSE)
	{
		for (i = 0; i<_tMesh->size(); i++)
			delete (*_tMesh)[i];
		delete _tMesh;
	}
	isMirror = GL_FALSE;
	_tMesh = new std::vector<Mesh *>;
}

void engine::Model::initMeshMirror(Model *m)
{
	GLuint i;
	if (_tMesh != NULL && isMirror == GL_FALSE)
	{
		for (i = 0; i<_tMesh->size(); i++)
			delete (*_tMesh)[i];
		delete _tMesh;
	}
	isMirror = GL_TRUE;
	_tMesh = m->_tMesh;
}

void engine::Model::config(ShaderProgram *gProgram, ShaderProgram *smProgram)
{
	_gProgram = gProgram;
	_smProgram = smProgram;

	_gMVPLocation = glGetUniformLocation(_gProgram->getId(), "MVP");
	_gNormalMatrixLocation = glGetUniformLocation(_gProgram->getId(), "normalMatrix");
	_gColorTextureLocation = glGetUniformLocation(_gProgram->getId(), "colorTexture");
	_gNMTextureLocation = glGetUniformLocation(_gProgram->getId(), "NMTexture");
	_gMaterialBlockIndex = glGetUniformBlockIndex(_gProgram->getId(), "material");

	_smMVPLocation = glGetUniformLocation(_smProgram->getId(), "MVP");
	_smColorTextureLocation = glGetUniformLocation(_smProgram->getId(), "colorTexture");
}

void engine::Model::createMesh(const GLsizei &sizeVertexArray, const GLfloat *vertexArray,
				 const GLsizei &sizeIndexArray, const GLuint *indexArray,
				 const GLchar *colorTexture, const GLchar *NMTexture,
				 const glm::vec4 &ambient, const glm::vec4 &diffuse, const glm::vec4 &specular, const GLfloat &shininess)
{
	Mesh *newone = new Mesh;
	GLuint colorTex, NMTex;

	loadTextureFromFile(colorTexture, &colorTex);
	loadTextureFromFile(NMTexture, &NMTex);

	newone->setColorTexture(colorTex);
	newone->setNMTexture(NMTex);
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

void engine::Model::loadFromFile(const GLchar *file)
{
	Assimp::Importer Importer;
	GLuint i, j;

	if (_tMesh != NULL && isMirror == GL_FALSE)
		_tMesh->clear();

	const aiScene *pScene = Importer.ReadFile(file, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace | aiProcess_JoinIdenticalVertices | aiProcess_OptimizeMeshes);
	if (!pScene)
	{
		std::cerr << "Unable to load the model: " << file << std::endl;
		exit(1);
	}

	std::vector<Vertex> vertices;
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

			Vertex v =
			{
				glm::vec3(pPos->x, pPos->y, pPos->z),
				glm::vec2(pTexCoord->x, pTexCoord->y),
				glm::vec3(pNormal->x, pNormal->y, pNormal->z),
				glm::vec3(pTangent->x, pTangent->y, pTangent->z),
			};

			vertices.push_back(v);
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
		{
			colorPath += dir + path.C_Str();
			NMPath += dir + "NM_" + path.C_Str();
		}
		else
		{
			colorPath = "resources/none.png";
			NMPath = "resources/NM_none.png";
		}

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

		createMesh((GLsizei)vertices.size() * sizeof(Vertex), (GLfloat *)&vertices[0],
			(GLsizei)indices.size() * sizeof(GLuint), &indices[0],
			colorPath.c_str(), NMPath.c_str(),
			glm::vec4(mat_ambient.r, mat_ambient.g, mat_ambient.b, mat_ambient.a), glm::vec4(mat_diffuse.r, mat_diffuse.g, mat_diffuse.b, mat_diffuse.a), glm::vec4(mat_specular.r, mat_specular.g, mat_specular.b, mat_specular.a),
			mat_shininess);

		vertices.clear();
		indices.clear();
	}
}

void engine::Model::sortMesh(void)
{
	qsort(&(*_tMesh)[0], _tMesh->size(), sizeof (*_tMesh)[0], comparMesh);
}

void engine::Model::matIdentity(void)
{
	*_modelMatrix = glm::mat4(1.0f);
}

void engine::Model::matTranslate(const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
	*_modelMatrix *= glm::translate(glm::vec3(x, y, z));
}

void engine::Model::matRotate(const GLfloat &angle, const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
	*_modelMatrix *= glm::rotate(angle * ((GLfloat)M_PI / 180), glm::vec3(x, y, z));
}

void engine::Model::matScale(const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
	*_modelMatrix *= glm::scale(glm::vec3(x, y, z));
}

glm::vec3 engine::Model::getPosition(void) const
{
	return glm::vec3((*_modelMatrix)[0][3], (*_modelMatrix)[1][3], (*_modelMatrix)[2][3]);
}

engine::Mesh *engine::Model::getMesh(const GLuint &num) const
{
	if(num>=_tMesh->size())
	{
		std::cerr << "Bad num Mesh" << std::endl;
		return NULL;
	}
	return (*_tMesh)[num];
}

void engine::Model::display(GBuffer *gbuf, Camera *cam) const
{
	GLuint i;

	gbuf->setGeometryState();

	glUseProgram(_gProgram->getId());

	glUniformMatrix4fv(_gMVPLocation, 1, GL_FALSE, glm::value_ptr(cam->getVPMatrix() * *_modelMatrix));
	glUniformMatrix4fv(_gNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(*_modelMatrix))));

	for(i=0 ; i<_tMesh->size(); i++)
        if((*_tMesh)[i]->getTransparency() == 1.0f)
			(*_tMesh)[i]->display(_gColorTextureLocation, _gNMTextureLocation, _gMaterialBlockIndex);

	glUseProgram(0);

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void engine::Model::displayTransparent(GBuffer *gbuf, Camera *cam) const
{
	GLuint i;

	gbuf->setGeometryState();

	glUseProgram(_gProgram->getId());

	glUniformMatrix4fv(_gMVPLocation, 1, GL_FALSE, glm::value_ptr(cam->getVPMatrix() * *_modelMatrix));
	glUniformMatrix4fv(_gNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(*_modelMatrix))));

	for (i = 0; i<_tMesh->size(); i++)
		if ((*_tMesh)[i]->getTransparency() != 1.0f)
			(*_tMesh)[i]->display(_gColorTextureLocation, _gNMTextureLocation, _gMaterialBlockIndex);

	glUseProgram(0);

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void engine::Model::displayShadowMap(Light *light) const
{
	GLuint i;

	light->getShadowMap()->setState();

	glUseProgram(_smProgram->getId());

	glUniformMatrix4fv(_smMVPLocation, 1, GL_FALSE, glm::value_ptr(light->getVPMatrix() * *_modelMatrix));

	for(i=0 ; i<_tMesh->size(); i++)
        if((*_tMesh)[i]->getTransparency() == 1.0f)
			(*_tMesh)[i]->displayShadow(_smColorTextureLocation);

	glUseProgram(0);

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}
