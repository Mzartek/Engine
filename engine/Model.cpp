#include <Engine/Model.hpp>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

engine::Model::Model(void)
{
	_tGLObject = NULL;
	_modelMatrix = new glm::mat4;
	_program = NULL;
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

void engine::Model::config(ShaderProgram *program)
{
	_program = program;
	_MVPLocation = glGetUniformLocation(_program->getId(), "MVP");
	_normalMatrixLocation = glGetUniformLocation(_program->getId(), "normalMatrix");
}

void engine::Model::createGLObject(const GLsizei &sizeVertexArray, const GLfloat *vertexArray,
				 const GLsizei &sizeIndexArray, const GLuint *indexArray,
				 const GLchar *pathTexture,
				 const GLfloat *ambient, const GLfloat *diffuse, const GLfloat *specular, const GLfloat *shininess)
{
	GLObject *newone = new GLObject;
	GLuint texture;

	loadTextureFromFile(pathTexture, &texture);

	newone->config(_program);
	newone->setTexture(texture);
	newone->setAmbient(ambient[0], ambient[1], ambient[2], ambient[3]);
	newone->setDiffuse(diffuse[0], diffuse[1], diffuse[2], diffuse[3]);
	newone->setSpecular(specular[0], specular[1], specular[2], specular[3]);
	newone->setShininess(shininess[0]);
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

	const aiScene *pScene = Importer.ReadFile(file, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
	if (!pScene)
	{
		std::cerr << "Unable to load the model: " << file << std::endl;
		return;
	}

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
	for (i = 0; i<pScene->mNumMeshes; i++)
	{
		//vertices.resize(pScene->mMeshes[i]->mNumVertices);
		for (j = 0; j<pScene->mMeshes[i]->mNumVertices; j++)
		{
			const aiVector3D *pPos = &(pScene->mMeshes[i]->mVertices[j]);
			const aiVector3D *pNormal = pScene->mMeshes[i]->HasNormals() ? &(pScene->mMeshes[i]->mNormals[j]) : &Zero3D;
			const aiVector3D *pTexCoord = pScene->mMeshes[i]->HasTextureCoords(0) ? &(pScene->mMeshes[i]->mTextureCoords[0][j]) : &Zero3D;

			Vertex v =
			{
				glm::vec3(pPos->x, pPos->y, pPos->z),
				glm::vec2(pTexCoord->x, pTexCoord->y),
				glm::vec3(pNormal->x, pNormal->y, pNormal->z)
			};

			vertices.push_back(v);
		}

		//vertices.resize(pScene->mMeshes[i]->mNumFaces * 3);
		for (j = 0; j < pScene->mMeshes[i]->mNumFaces; j++)
		{
			indices.push_back(pScene->mMeshes[i]->mFaces[j].mIndices[0]);
			indices.push_back(pScene->mMeshes[i]->mFaces[j].mIndices[1]);
			indices.push_back(pScene->mMeshes[i]->mFaces[j].mIndices[2]);
		}

		aiString path;
		std::string fullPath;
		if (pScene->mMaterials[pScene->mMeshes[i]->mMaterialIndex]->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
			fullPath = getDir(file) + path.C_Str();
		else
			fullPath = "resources/none.png";

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
			&fullPath[0],
			(GLfloat *)&mat_ambient, (GLfloat *)&mat_diffuse, (GLfloat *)&mat_specular,
			&mat_shininess);

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

	if(_program == NULL)
	{
		std::cerr << "You need to configure the Model before" << std::endl;
		return;
	}
	if(cam == NULL)
	{
		std::cerr << "Bad Camera" << std::endl;
		return;
	}

	glUseProgram(_program->getId());

	// MVP Matrix
	glUniformMatrix4fv(_MVPLocation, 1, GL_FALSE, glm::value_ptr(cam->getVPMatrix() * *_modelMatrix));

	// Normal Matrix	
	glUniformMatrix4fv(_normalMatrixLocation, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(*_modelMatrix))));

	glUseProgram(0);

	for(i=0 ; i<_tGLObject->size(); i++)
        if((*_tGLObject)[i]->getTransparency() == 1.0f)
            (*_tGLObject)[i]->display(g);
}

void engine::Model::displayShadow(Light *l) const
{
	GLuint i;

	if(l == NULL)
	{
		std::cerr << "Bad Light!" << std::endl;
		return;
	}
	if(l->getShadowMap() == NULL)
	{
		std::cerr << "You need to config the ShadowMap before!" << std::endl;
		return;
	}

	glUseProgram(l->getShadowMap()->getProgramId());

	glUniformMatrix4fv(l->getShadowMap()->getMVPLocation(), 1, GL_FALSE, glm::value_ptr(l->getVPMatrix() * *_modelMatrix));

	glUseProgram(0);

	for(i=0 ; i<_tGLObject->size(); i++)
        if((*_tGLObject)[i]->getTransparency() == 1.0f)
            (*_tGLObject)[i]->displayShadow(l);
}
