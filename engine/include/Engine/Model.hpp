#ifndef MODEL
#define MODEL

#include "Mesh.hpp"
#include "Light.hpp"
#include "ShaderProgram.hpp"
#include "Camera.hpp"

namespace engine
{
	class DLLAPI Model : public Object
	{
	private:
		GLboolean isMirror;
		std::vector<Mesh *> *_tMesh;
		glm::mat4 *_modelMatrix;
		// ShaderProgram
		ShaderProgram *_gProgram;
		ShaderProgram *_smProgram;
		// Geometry Location
		GLint _gMVPLocation;
		GLint _gNormalMatrixLocation;
		GLint _gColorTextureLocation;
		GLint _gNMTextureLocation;
		GLuint _gMaterialBlockIndex;
		// ShadowMap Location
		GLint _smMVPLocation;
		GLint _smColorTextureLocation;
	public:
		Model();
		~Model();
		void initMeshArray(void);
		void initMeshMirror(Model *m);
		void config(ShaderProgram *gProgram, ShaderProgram *smProgram);
		void createMesh(const GLsizei &sizeVertexArray, const GLfloat *vertexArray,
				  const GLsizei &sizeIndexArray, const GLuint *indexArray,
				  const GLchar *colorTexture, const GLchar *NMTexture,
				  const glm::vec4 &ambient, const glm::vec4 &diffuse, const glm::vec4 &specular, const GLfloat &shininess);
		void loadFromFile(const GLchar *file);
		void sortMesh(void);
		void matIdentity(void);
		void matTranslate(const GLfloat &x, const GLfloat &y, const GLfloat &z);
		void matRotate(const GLfloat &angle, const GLfloat &x, const GLfloat &y, const GLfloat &z);
		void matScale(const GLfloat &x, const GLfloat &y, const GLfloat &z);
		glm::vec3 getPosition(void) const;
		Mesh *getMesh(const GLuint &num) const;
		void display(GBuffer *g, Camera *cam) const;
		void displayTransparent(GBuffer *gbuf, Camera *cam) const;
		void displayShadow(Light *light) const;
	};
}


#endif
