#ifndef MODEL_HEADER
#define MODEL_HEADER

#include "Object.hpp"

namespace Engine
{
     struct Vertex;
     class Mesh;
     class Buffer;
     class ShaderProgram;
     class GBuffer;
     class Camera;
     class DirLight;
     class SpotLight;
     class Texture;

     class DLLAPI Model : public Object
     {
     private:
	  struct
	  {
	       glm::mat4 MVP;
	       glm::mat4 projection;
	       glm::mat4 view;
	       glm::mat4 model;
	       glm::mat4 normal;
	  } _matrix;

	  struct
	  {
	       glm::vec3 ALIGN(16) position;
	       glm::vec3 ALIGN(16) target;
	  } _camera;

	  GLboolean _isMirror;
	  std::vector<Mesh *> *_tMesh;
	  Buffer *_matrixBuffer;
	  Buffer *_cameraBuffer;
	  glm::vec3 *_position;
	  glm::vec3 *_rotation;
	  glm::vec3 *_scale;
	  glm::mat4 *_modelMatrix;
	  glm::mat4 *_normalMatrix;
	  GLboolean _needMatModel;
	  GLboolean _needMatNormal;
	  Texture *_cubeTexture;
	  ShaderProgram *_gProgram;
	  ShaderProgram *_smProgram;

	  void genMatModel(void) const;
	  void genMatNormal(void) const;
	  void checkMatrix(void);
	  void deleteMesh(void);
     public:
	  Model(ShaderProgram *gProgram, ShaderProgram *smProgram);
	  Model(Model *model, ShaderProgram *gProgram, ShaderProgram *smProgram);
	  ~Model(void);
	  void addMesh(const GLsizei &numVertex, const Vertex *vertexArray,
		       const GLsizei &numIndex, const GLuint *indexArray,
		       const GLchar *colorTexture, const GLchar *NMTexture,
		       const glm::vec4 &ambient, const glm::vec4 &diffuse, const glm::vec4 &specular, const GLfloat &shininess);
	  void loadFromFile(const GLchar *file, const GLchar *defaultTex, const GLchar *defaultNM);
	  void sortMesh(void);
	  void setPosition(const glm::vec3 &position);
	  void setRotation(const glm::vec3 &rotation);
	  void setScale(const glm::vec3 &scale);
	  void setCubeTexture(Texture *cubeTex);
	  glm::vec3 getPosition(void) const;
	  glm::vec3 getRotation(void) const;
	  glm::vec3 getScale(void) const;
	  Mesh *getMesh(const GLuint &num) const;
	  void display(GBuffer *g, Camera *cam);
	  void displayTransparent(GBuffer *gbuf, Camera *cam);
	  void displayShadowMap(DirLight *light);
	  void displayShadowMap(SpotLight *light);
     };
}


#endif
