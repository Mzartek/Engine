#ifndef MODEL
#define MODEL

#include "GLObject.hpp"
#include "Light.hpp"
#include "ShaderProgram.hpp"
#include "Camera.hpp"

namespace engine
{
	class DLLAPI Model : public Object
	{
	private:
		GLboolean isMirror;
		std::vector<GLObject *> *_tGLObject;
		glm::mat4 *_modelMatrix;
		// ShaderProgram
		ShaderProgram *_gProgram;
		ShaderProgram *_smProgram;
		// Geometry Location
		GLint _gMVPLocation;
		GLint _gNormalMatrixLocation;
		GLint _gColorTextureLocation;
		GLint _gMaterialLocation;
		// ShadowMap Location
		GLint _smMVPLocation;
		GLint _smColorTextureLocation;
	public:
		Model();
		~Model();
		void initGLObjectArray(void);
		void initGLObjectMirror(Model *m);
		void config(ShaderProgram *gProgram, ShaderProgram *smProgram);
		void createGLObject(const GLsizei &sizeVertexArray, const GLfloat *vertexArray,
				  const GLsizei &sizeIndexArray, const GLuint *indexArray,
				  const GLchar *pathTexture,
				  const glm::vec4 &ambient, const glm::vec4 &diffuse, const glm::vec4 &specular, const GLfloat &shininess);
		void loadFromFile(const GLchar *file);
		void sortGLObject(void);
		void matIdentity(void);
		void matTranslate(const GLfloat &x, const GLfloat &y, const GLfloat &z);
		void matRotate(const GLfloat &angle, const GLfloat &x, const GLfloat &y, const GLfloat &z);
		void matScale(const GLfloat &x, const GLfloat &y, const GLfloat &z);
		glm::vec3 getPosition(void) const;
		GLObject *getGLObject(const GLuint &num) const;
		void display(GBuffer *g, Camera *cam) const;
		void displayShadow(Light *l) const;
	};
}


#endif
