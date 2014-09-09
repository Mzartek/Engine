#include <Engine/Model.hpp>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

engine::Model::Model(void)
{
	_tGLObject = NULL;
	_modelMatrix = new glm::mat4;
	_gProgram = NULL;
	_smProgram = NULL;
}

engine::Model::~Model(void)
{
	GLuint i;
	if (_tGLObject != NULL && isMirror == GL_FALSE)
	{
		for (i = 0; i<_tGLObject->size(); i++)
			delete (*_tGLObject)[i];
		delete _tGLObject;
	}
	delete _modelMatrix;
}

void engine::Model::initGLObjectArray(void)
{
	GLuint i;
	if (_tGLObject != NULL && isMirror == GL_FALSE)
	{
		for (i = 0; i<_tGLObject->size(); i++)
			delete (*_tGLObject)[i];
		delete _tGLObject;
	}
	isMirror = GL_FALSE;
	_tGLObject = new std::vector<GLObject *>;
}

void engine::Model::initGLObjectMirror(Model *m)
{
	GLuint i;
	if (_tGLObject != NULL && isMirror == GL_FALSE)
	{
		for (i = 0; i<_tGLObject->size(); i++)
			delete (*_tGLObject)[i];
		delete _tGLObject;
	}
	isMirror = GL_TRUE;
	_tGLObject = m->_tGLObject;
}

void engine::Model::config(ShaderProgram *gProgram, ShaderProgram *smProgram)
{
	_gProgram = gProgram;
	_gMVPLocation = glGetUniformLocation(_gProgram->getId(), "MVP");
	_gNormalMatrixLocation = glGetUniformLocation(_gProgram->getId(), "normalMatrix");
	_gColorTextureLocation = glGetUniformLocation(_gProgram->getId(), "colorTexture");
	_gNMTextureLocation = glGetUniformLocation(_gProgram->getId(), "NMTexture");
	_gMaterialLocation = glGetUniformBlockIndex(_gProgram->getId(), "material");

	_smProgram = smProgram;
	_smMVPLocation = glGetUniformLocation(_smProgram->getId(), "MVP");
	_smColorTextureLocation = glGetUniformLocation(_smProgram->getId(), "colorTexture");
}

void engine::Model::createGLObject(const GLsizei &sizeVertexArray, const GLfloat *vertexArray,
				 const GLsizei &sizeIndexArray, const GLuint *indexArray,
				 const GLchar *colorTexture, const GLchar *NMTexture,
				 const glm::vec4 &ambient, const glm::vec4 &diffuse, const glm::vec4 &specular, const GLfloat &shininess)
{
	GLObject *newone = new GLObject;
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

	_tGLObject->push_back(newone);
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

	if (_tGLObject != NULL && isMirror == GL_FALSE)
		_tGLObject->clear();

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

		createGLObject((GLsizei)vertices.size() * sizeof(Vertex), (GLfloat *)&vertices[0],
			(GLsizei)indices.size() * sizeof(GLuint), &indices[0],
			colorPath.c_str(), NMPath.c_str(),
			glm::vec4(mat_ambient.r, mat_ambient.g, mat_ambient.b, mat_ambient.a), glm::vec4(mat_diffuse.r, mat_diffuse.g, mat_diffuse.b, mat_diffuse.a), glm::vec4(mat_specular.r, mat_specular.g, mat_specular.b, mat_specular.a),
			mat_shininess);

		vertices.clear();
		indices.clear();
	}
}

void engine::Model::sortGLObject(void)
{
	qsort(&(*_tGLObject)[0], _tGLObject->size(), sizeof (*_tGLObject)[0], comparGLObject);
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

engine::GLObject *engine::Model::getGLObject(const GLuint &num) const
{
	if(num>=_tGLObject->size())
	{
		std::cerr << "Bad num GLObject" << std::endl;
		return NULL;
	}
	return (*_tGLObject)[num];
}

void engine::Model::display(GBuffer *g, Camera *cam) const
{
	GLuint i;

	g->setGeometryConfig();

	glUseProgram(_gProgram->getId());

	glUniformMatrix4fv(_gMVPLocation, 1, GL_FALSE, glm::value_ptr(cam->getVPMatrix() * *_modelMatrix));
	glUniformMatrix4fv(_gNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(*_modelMatrix))));

	for(i=0 ; i<_tGLObject->size(); i++)
        if((*_tGLObject)[i]->getTransparency() == 1.0f)
			(*_tGLObject)[i]->display(_gColorTextureLocation, _gNMTextureLocation,_gMaterialLocation);

	glUseProgram(0);
}

void engine::Model::displayShadow(Light *l) const
{
	GLuint i;

	l->getShadowMap()->setConfig();

	glUseProgram(_smProgram->getId());

	glUniformMatrix4fv(_smMVPLocation, 1, GL_FALSE, glm::value_ptr(l->getVPMatrix() * *_modelMatrix));

	for(i=0 ; i<_tGLObject->size(); i++)
        if((*_tGLObject)[i]->getTransparency() == 1.0f)
			(*_tGLObject)[i]->displayShadow(_smColorTextureLocation);

	glUseProgram(0);
}
