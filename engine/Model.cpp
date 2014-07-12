#include <Engine/Model.hpp>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

engine::Model::Model(void)
{
	_tObject = NULL;
	_program = NULL;
	matIdentity();
}

engine::Model::~Model(void)
{
	GLuint i;
	if(_tObject != NULL && isMirror == GL_FALSE)
	{		
		for(i=0 ; i<_tObject->size(); i++)
			delete (*_tObject)[i];
		delete _tObject;
	}
}

void engine::Model::initObjectArray(void)
{
	GLuint i;
	if(_tObject != NULL && isMirror == GL_FALSE)
	{		
		for(i=0 ; i<_tObject->size(); i++)
			delete (*_tObject)[i];
		delete _tObject;
	}
	isMirror = GL_FALSE;
	_tObject = new std::vector<Object *>;
}

void engine::Model::initObjectMirror(Model *m)
{
	isMirror = GL_TRUE;
	_tObject = m->_tObject;
}

void engine::Model::config(ShaderProgram *program)
{
	_program = program;
	_MVPLocation = glGetUniformLocation(_program->getId(), "MVP");
	_modelMatrixLocation = glGetUniformLocation(_program->getId(), "modelMatrix");
	_normalMatrixLocation = glGetUniformLocation(_program->getId(), "normalMatrix");
}

void engine::Model::createObject(const GLsizei &sizeVertexArray, const GLfloat *vertexArray,
				 const GLsizei &sizeIndexArray, const GLuint *indexArray,
				 const std::string pathTexture,
				 const GLfloat *ambient, const GLfloat *diffuse, const GLfloat *specular, const GLfloat *shininess)
{
	Object *newone = new Object();
	GLuint texture;
  
	loadTextureFromFile(pathTexture, &texture);

	newone->setShaderProgram(_program);
	newone->setTexture(texture);
	newone->setAmbient(ambient[0], ambient[1], ambient[2], ambient[3]);
	newone->setDiffuse(diffuse[0], diffuse[1], diffuse[2], diffuse[3]);
	newone->setSpecular(specular[0], specular[1], specular[2], specular[3]);
	newone->setShininess(shininess[0]);
	newone->load(sizeVertexArray, vertexArray,
		     sizeIndexArray, indexArray);
  
	_tObject->push_back(newone);
}

static std::string getDir(std::string file)
{
	GLuint size, i;
	std::string path;

	for (size = i = 0; file[i] != '\0'; i++)
		if (file[i] == '/')
			size = i + 1;

	path.insert(0, file, 0, size);

	return path;
}

void engine::Model::loadFromFile(const std::string file)
{
	Assimp::Importer Importer;
	GLuint i, j;

	if (_tObject != NULL && isMirror == GL_FALSE)
	{
		_tObject->clear();
	}

	const aiScene *pScene = Importer.ReadFile(file, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);
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
				Vector3D<GLfloat>(pPos->x, pPos->y, pPos->z),
				Vector2D<GLfloat>(pTexCoord->x, pTexCoord->y),
				Vector3D<GLfloat>(pNormal->x, pNormal->y, pNormal->z)
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
			fullPath = getDir(file) + path.data;
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

		createObject((GLsizei)vertices.size() * sizeof(Vertex), (GLfloat *)&vertices[0],
			(GLsizei)indices.size() * sizeof(GLuint), &indices[0],
			fullPath,
			(GLfloat *)&mat_ambient, (GLfloat *)&mat_diffuse, (GLfloat *)&mat_specular,
			&mat_shininess);

		vertices.clear();
		indices.clear();
	}
}

void engine::Model::sortObject(void)
{
	qsort(&(*_tObject)[0], _tObject->size(), sizeof (*_tObject)[0], comparObject);
}

void engine::Model::matIdentity(void)
{
	matrixLoadIdentity(_modelMatrix);
}

void engine::Model::matTranslate(const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
	matrixTranslate(_modelMatrix, x, y, z);
}

void engine::Model::matRotate(const GLfloat &angle, const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
	matrixRotate(_modelMatrix, angle, x, y, z);
}

void engine::Model::matScale(const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
	matrixScale(_modelMatrix, x, y, z);
}

engine::Vector3D<GLfloat> engine::Model::getPosition(void) const
{
	engine::Vector3D<GLfloat> tmp;
	tmp.x = _modelMatrix[12];
	tmp.y = _modelMatrix[13];
	tmp.z = _modelMatrix[14];
	return tmp;
}

engine::Object *engine::Model::getObject(GLuint num) const
{
	if(num>=_tObject->size())
	{
		std::cerr << "Bad num Object" << std::endl;
		return NULL;
	}
	return (*_tObject)[num];
}
  
void engine::Model::display(GBuffer *g, Camera *cam) const
{
	GLuint i;
	GLfloat tmp[16];
  
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
	matrixMultiply(tmp, cam->getMatrix(), _modelMatrix);
	glUniformMatrix4fv(_MVPLocation, 1, GL_FALSE, tmp);

	// Model Matrix
	glUniformMatrix4fv(_modelMatrixLocation, 1, GL_FALSE, _modelMatrix);

	// Normal Matrix
	matrixNormalFromModel(tmp, _modelMatrix);
	glUniformMatrix3fv(_normalMatrixLocation, 1, GL_FALSE, tmp);
  
	glUseProgram(0);
  
	for(i=0 ; i<_tObject->size(); i++)
		(*_tObject)[i]->display(g);
}

void engine::Model::displayShadow(Light *l) const
{
	GLuint i;
	GLfloat tmp[16];

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
	
	matrixMultiply(tmp, l->getMatrix(), _modelMatrix);
	glUniformMatrix4fv(l->getShadowMap()->getMVPLocation(), 1, GL_FALSE, tmp);
	
	glUseProgram(0);

	for(i=0 ; i<_tObject->size(); i++)
		(*_tObject)[i]->displayShadow(l);
}
