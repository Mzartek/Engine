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

		GLboolean isMirror;
		std::vector<Mesh *> *_tMesh;
		Buffer *_matrixBuffer;
		Buffer *_cameraBuffer;
		glm::mat4 *_modelMatrix;
		glm::mat4 *_normalMatrix;
		ShaderProgram *_gProgram;
		ShaderProgram *_smProgram;
	public:
		Model(ShaderProgram *gProgram, ShaderProgram *smProgram);
		~Model(void);
		void initMeshArray(void);
		void initMeshMirror(Model *m);
		void addMesh(const GLsizei &numVertex, const Vertex *vertexArray,
				  const GLsizei &numIndex, const GLuint *indexArray,
				  const GLchar *colorTexture, const GLchar *NMTexture,
				  const glm::vec4 &ambient, const glm::vec4 &diffuse, const glm::vec4 &specular, const GLfloat &shininess);
		void loadFromFile(const GLchar *file);
		void sortMesh(void);
		void matIdentity(void) const;
		void matTranslate(const GLfloat &x, const GLfloat &y, const GLfloat &z) const;
		void matRotate(const GLfloat &angle, const GLfloat &x, const GLfloat &y, const GLfloat &z) const;
		void matScale(const GLfloat &x, const GLfloat &y, const GLfloat &z) const;
		void genMatNormal(void) const;
		glm::vec3 getPosition(void) const;
		Mesh *getMesh(const GLuint &num) const;
		void display(GBuffer *g, Camera *cam);
		void displayTransparent(GBuffer *gbuf, Camera *cam);
		void displayShadowMap(DirLight *light);
		void displayShadowMap(SpotLight *light);
	};
}


#endif
