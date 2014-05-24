#ifndef OBJECT
#define OBJECT

#include "GLHead.hpp"
#include "Renderer.hpp"
#include "Light.hpp"
#include "GBuffer.hpp"

namespace engine
{
	class DLLAPI Object
	{
		friend int comparObject(const void *p1, const void *p2);
	private:
		Renderer *_renderer;
		GLuint _idTexture;
		GLuint _idVAO;
		GLuint _idVBO;
		GLuint _idIBO;
		GLfloat _matAmbient[4];
		GLfloat _matDiffuse[4];
		GLfloat _matSpecular[4];
		GLfloat _matShininess[1];
		GLsizei _numElement;
	public:
		Object(void);
		~Object(void);
		void setRenderer(Renderer *renderer);
		void setTexture(const GLuint &id);
		void setAmbient(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w);
		void setDiffuse(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w);
		void setSpecular(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w);
		void setShininess(const GLfloat &x);
		GLfloat getTransparency(void);
		void load(const GLsizei &sizeVertexArray, const GLfloat *vertexArray,
			  const GLsizei &sizeIndexArray, const GLuint *indexArray);
		void display(void) const;
		void displayShadow(Light *l) const;
		void displayOnGBuffer(GBuffer *g) const;
	};
  
	int comparObject(const void *p1, const void *p2);
  
}


#endif
