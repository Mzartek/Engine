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
		GLint _screenWidthLocation;
		GLint _screenHeightLocation;
		GLint _MVPLocation;
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
		void sortObject(void);
		void matIdentity(void);
		void matTranslate(const GLfloat &x, const GLfloat &y, const GLfloat &z);
		void matRotate(const GLfloat &angle, const GLfloat &x, const GLfloat &y, const GLfloat &z);
		void matScale(const GLfloat &x, const GLfloat &y, const GLfloat &z);
		Vector3D<GLfloat> getPosition(void) const;
		Object *getObject(GLuint num) const;
		void display(Window *win, Camera *cam, LBuffer *l) const;
		void displayOnGBuffer(Camera *cam, GBuffer *g) const;
		void displayShadow(Light *l) const;
	};
}
    

#endif
