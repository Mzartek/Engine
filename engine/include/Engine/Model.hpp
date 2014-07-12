#ifndef MODEL
#define MODEL

#include "Object.hpp"
#include "Light.hpp"
#include "GBuffer.hpp"
#include "ShaderProgram.hpp"
#include "Camera.hpp"
#include "Window.hpp"

namespace engine
{
	class DLLAPI Model
	{
	private:
		GLboolean isMirror;
		std::vector<Object *> *_tObject;
		GLfloat _modelMatrix[16];
		ShaderProgram *_program;
		GLint _MVPLocation;
		GLint _modelMatrixLocation;
		GLint _normalMatrixLocation;
	public:
		Model();
		~Model();
		void initObjectArray(void);
		void initObjectMirror(Model *m);
		void config(ShaderProgram *program);
		void createObject(const GLsizei &sizeVertexArray, const GLfloat *vertexArray,
				  const GLsizei &sizeIndexArray, const GLuint *indexArray,
				  const std::string pathTexture,
				  const GLfloat *ambient, const GLfloat *diffuse, const GLfloat *specular, const GLfloat *shininess);
		void loadFromFile(const std::string file);
		void sortObject(void);
		void matIdentity(void);
		void matTranslate(const GLfloat &x, const GLfloat &y, const GLfloat &z);
		void matRotate(const GLfloat &angle, const GLfloat &x, const GLfloat &y, const GLfloat &z);
		void matScale(const GLfloat &x, const GLfloat &y, const GLfloat &z);
		Vector3D<GLfloat> getPosition(void) const;
		Object *getObject(GLuint num) const;
		void display(GBuffer *g, Camera *cam) const;
		void displayShadow(Light *l) const;
	};
}
    

#endif
