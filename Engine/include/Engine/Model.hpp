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
     class PerspCamera;
     class DirLight;
     class SpotLight;
     class TextureCube;
	 class DepthMap;

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
		  glm::vec3 ALIGN(16) forward;
		  glm::vec3 ALIGN(16) left;
		  glm::vec3 ALIGN(16) up;
	  } _camera;

	  GLboolean _isMirror;
	  
	  std::vector<Mesh *> *_tMesh;
	  std::vector<Object *> *_tObject;
	  
	  Buffer *_matrixBuffer;
	  Buffer *_cameraBuffer;
	  
	  glm::vec3 *_position;
	  glm::vec3 *_scale;
	  glm::quat *_rotation;
	  
	  glm::mat4 *_modelMatrix;
	  glm::mat4 *_normalMatrix;
	  
	  GLboolean _needMatModel;
	  GLboolean _needMatNormal;
	  
	  TextureCube *_cubeTexture;
	  
	  ShaderProgram *_gProgram;
	  ShaderProgram *_smProgram;

	  void genMatModel(void) const;
	  void genMatNormal(void) const;
	  void checkMatrix(void);
     public:
	  Model(ShaderProgram *gProgram, ShaderProgram *smProgram);
	  Model(Model *model, ShaderProgram *gProgram, ShaderProgram *smProgram);
	  ~Model(void);
	  void addMesh(Mesh *mesh);
	  void loadFromFile(const GLchar *inFile);
	  void sortMesh(void);
	  void setPosition(const glm::vec3 &position);
	  void setScale(const glm::vec3 &scale);
	  void setRotation(const glm::vec3 &rotation);
	  void setRotation(const GLfloat &angle, const glm::vec3 &axis);
	  void setCubeTexture(TextureCube *cubeTexture);
	  glm::vec3 getPosition(void) const;
	  glm::vec3 getScale(void) const;
	  glm::vec3 getEulerAnglesRotation(void) const;
	  std::pair<GLfloat, glm::vec3> getAngleAxisRotation(void) const;
	  Mesh *getMesh(const GLuint &num) const;
	  void display(GBuffer *g, PerspCamera *cam);
	  void displayTransparent(GBuffer *gbuf, PerspCamera *cam);
	  void displayDepthMap(DepthMap *dmap, Camera *cam);
	  void displayDepthMap(DepthMap *dmaps, DirLight *light);
	  void displayDepthMap(DepthMap *dmap, SpotLight *light);
     };
}


#endif
