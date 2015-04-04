#include <Engine/Model.hpp>
#include <Engine/Mesh.hpp>
#include <Engine/Buffer.hpp>
#include <Engine/ShaderProgram.hpp>
#include <Engine/GBuffer.hpp>
#include <Engine/Camera.hpp>
#include <Engine/DirLight.hpp>
#include <Engine/SpotLight.hpp>
#include <Engine/ShadowMap.hpp>
#include <Engine/TextureCube.hpp>

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

void Engine::Model::deleteMesh(void)
{
     if (_tMesh != NULL && _isMirror != GL_TRUE)
     {
	  for (GLuint i = 0; i<_tMesh->size(); i++)
	       delete (*_tMesh)[i];
	  delete _tMesh;
     }
}

Engine::Model::Model(ShaderProgram *gProgram, ShaderProgram *smProgram)
     : _isMirror(GL_FALSE), _tMesh(NULL), _needMatModel(GL_TRUE), _needMatNormal(GL_TRUE), _cubeTexture(NULL), _gProgram(gProgram), _smProgram(smProgram)
{
     _tMesh = new std::vector<Mesh *>;
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
     glUniform1i(glGetUniformLocation(_gProgram->getId(), "colorTexture"), 0);
     glUniform1i(glGetUniformLocation(_gProgram->getId(), "NMTexture"), 1);
     glUseProgram(_smProgram->getId());
     glUniform1i(glGetUniformLocation(_smProgram->getId(), "colorTexture"), 0);
}

Engine::Model::Model(Model *model, ShaderProgram *gProgram, ShaderProgram *smProgram)
     : _isMirror(GL_TRUE), _tMesh(NULL), _needMatModel(GL_TRUE), _needMatNormal(GL_TRUE), _cubeTexture(NULL), _gProgram(gProgram), _smProgram(smProgram)
{
     _tMesh = model->_tMesh;
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
     glUniform1i(glGetUniformLocation(_gProgram->getId(), "colorTexture"), 0);
     glUniform1i(glGetUniformLocation(_gProgram->getId(), "NMTexture"), 1);
     glUniform1i(glGetUniformLocation(_gProgram->getId(), "NMTexture"), 1);
     glUseProgram(_smProgram->getId());
     glUniform1i(glGetUniformLocation(_smProgram->getId(), "colorTexture"), 0);
}

Engine::Model::~Model(void)
{
     deleteMesh();

     delete _matrixBuffer;
     delete _cameraBuffer;
     delete _position;
     delete _rotation;
     delete _scale;
     delete _modelMatrix;
     delete _normalMatrix;
}

void Engine::Model::addMesh(const GLsizei &numVertex, const Vertex *vertexArray,
			    const GLsizei &numIndex, const GLuint *indexArray,
			    const GLchar *colorTexture, const GLchar *NMTexture,
			    const glm::vec4 &ambient, const glm::vec4 &diffuse, const glm::vec4 &specular, const GLfloat &shininess)
{
     Mesh *newone = new Mesh;

     newone->loadColorTexture(colorTexture);
     newone->loadNMTexture(NMTexture);
     newone->setAmbient(ambient);
     newone->setDiffuse(diffuse);
     newone->setSpecular(specular);
     newone->setShininess(shininess);
     newone->load(numVertex, vertexArray,
		  numIndex, indexArray);

     _tMesh->push_back(newone);
}

void Engine::Model::loadFromFile(const GLchar *file, const GLchar *defaultTex, const GLchar *defaultNM)
{
     Assimp::Importer Importer;
     GLuint i, j;

     if (_isMirror == GL_TRUE)
     {
	  std::cerr << "Can't load a mirror model" << std::endl;
	  exit(1);
     }

     const aiScene *pScene = Importer.ReadFile(file, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace | aiProcess_JoinIdenticalVertices | aiProcess_OptimizeMeshes);
     if (!pScene)
     {
	  std::string error = "Unable to load the model: ";
	  error.append(file);
	  std::cout << error << std::endl;
	  exit(1);
     }

     Vertex tmpVertex;
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

	       tmpVertex.position.x = pPos->x, tmpVertex.position.y = pPos->y, tmpVertex.position.z = pPos->z;
	       tmpVertex.texCoord.x = pTexCoord->x, tmpVertex.texCoord.y = pTexCoord->y;
	       tmpVertex.normal.x = pNormal->x, tmpVertex.normal.y = pNormal->y, tmpVertex.normal.z = pNormal->z;
	       tmpVertex.tangent.x = pTangent->x, tmpVertex.tangent.y = pTangent->y, tmpVertex.tangent.z = pTangent->z;

	       vertices.push_back(tmpVertex);
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
	       colorPath = defaultTex;
	  if (pScene->mMaterials[pScene->mMeshes[i]->mMaterialIndex]->GetTexture(aiTextureType_NORMALS, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
	       NMPath += dir + path.C_Str();
	  else
	       NMPath = defaultNM;

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

	  this->addMesh((GLsizei)vertices.size(), vertices.data(),
			(GLsizei)indices.size(), indices.data(),
			colorPath.c_str(), NMPath.c_str(),
			glm::vec4(mat_ambient.r, mat_ambient.g, mat_ambient.b, mat_ambient.a), glm::vec4(mat_diffuse.r, mat_diffuse.g, mat_diffuse.b, mat_diffuse.a), glm::vec4(mat_specular.r, mat_specular.g, mat_specular.b, mat_specular.a),
			mat_shininess);

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
     if(num>=_tMesh->size())
     {
	  std::cerr << "Bad num Mesh" << std::endl;
	  return NULL;
     }
     return (*_tMesh)[num];
}

void Engine::Model::display(GBuffer *gbuf, Camera *cam)
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

     for(GLuint i = 0 ; i<_tMesh->size(); i++)
	  if((*_tMesh)[i]->getTransparency() == 1.0f)
	  {
	       if (_cubeTexture)
		    (*_tMesh)[i]->display(_cubeTexture);		    
	       else
		    (*_tMesh)[i]->display();
	  }
}

void Engine::Model::displayTransparent(GBuffer *gbuf, Camera *cam)
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

     for (GLuint i = 0; i<_tMesh->size(); i++)
	  if ((*_tMesh)[i]->getTransparency() != 1.0f)
	  {
	       if (_cubeTexture)
		    (*_tMesh)[i]->display(_cubeTexture);		    
	       else
		    (*_tMesh)[i]->display();
	  }
}

void Engine::Model::displayShadowMap(DirLight *light)
{
     checkMatrix();

     glUseProgram(_smProgram->getId());

     _matrix.model = *_modelMatrix;
     _matrix.normal = *_normalMatrix;

     for (GLuint i = 0; i < CSM_NUM; i++)
     {
	  light->getShadowMap(i)->setState();

	  _matrix.MVP = light->getVPMatrix(i) * *_modelMatrix;
	  _matrix.projection = light->getProjectionMatrix(i);
	  _matrix.view = light->getViewMatrix(i);

	  _matrixBuffer->updateStoreMap(&_matrix);
	  glBindBufferBase(GL_UNIFORM_BUFFER, 0, _matrixBuffer->getId());

	  for (GLuint j = 0; j<_tMesh->size(); j++)
	       if ((*_tMesh)[j]->getTransparency() == 1.0f)
		    (*_tMesh)[j]->displayShadow();
     }
}

void Engine::Model::displayShadowMap(SpotLight *light)
{
     checkMatrix();

     light->getShadowMap()->setState();

     glUseProgram(_smProgram->getId());

     _matrix.MVP = light->getVPMatrix() * *_modelMatrix;
     _matrix.projection = light->getProjectionMatrix();
     _matrix.view = light->getViewMatrix();
     _matrix.model = *_modelMatrix;
     _matrix.normal = *_normalMatrix;
     _matrixBuffer->updateStoreMap(&_matrix);
     glBindBufferBase(GL_UNIFORM_BUFFER, 0, _matrixBuffer->getId());

     for (GLuint i = 0; i<_tMesh->size(); i++)
	  if ((*_tMesh)[i]->getTransparency() == 1.0f)
	       (*_tMesh)[i]->displayShadow();
}
