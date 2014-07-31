#ifndef GL_OBJECT
#define GL_OBJECT

#include "ShaderProgram.hpp"
#include "Light.hpp"
#include "GBuffer.hpp"

namespace engine
{
	class DLLAPI GLObject : public Object
	{
		friend int comparGLObject(const void *p1, const void *p2);
	private:
		GLuint _idTexture;
		GLuint _idVAO;
		GLuint _idVBO;
		GLuint _idIBO;
		GLfloat _matAmbient[4];
		GLfloat _matDiffuse[4];
		GLfloat _matSpecular[4];
		GLfloat _matShininess[1];
		GLsizei _numElement;
		ShaderProgram *_gProgram;
		GLint _gNormalTextureLocation;
		GLint _gMaterialTextureLocation;
		GLint _gDepthTextureLocation;
		GLint _gColorTextureLocation;
		GLint _gMatAmbientLocation;
		GLint _gMatDiffuseLocation;
		GLint _gMatSpecularLocation;
		GLint _gMatShininessLocation;
		GLint _gScreenLocation;
	public:
		GLObject(void);
		~GLObject(void);
		void config(ShaderProgram *gProgram);
		void setTexture(const GLuint &id);
		void setAmbient(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w);
		void setDiffuse(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w);
		void setSpecular(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w);
		void setShininess(const GLfloat &x);
		GLfloat getTransparency(void);
		void load(const GLsizei &sizeVertexArray, const GLfloat *vertexArray,
			  const GLsizei &sizeIndexArray, const GLuint *indexArray);
		void display(GBuffer *g) const;
		void displayShadow(Light *l) const;
	};

	int comparGLObject(const void *p1, const void *p2);

}


#endif
