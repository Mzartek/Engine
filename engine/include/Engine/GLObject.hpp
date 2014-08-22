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
		GLuint _idMaterialBuffer;
		struct material
		{
			glm::vec4 ambient;
			glm::vec4 diffuse;
			glm::vec4 specular;
			GLfloat shininess;
		} _material;
		GLsizei _numElement;
		// Do not delete it
		ShaderProgram *_gProgram;
		// Location or Index
		GLint _gColorTextureLocation;
		GLuint _gMaterialIndex;
	public:
		GLObject(void);
		~GLObject(void);
		void config(ShaderProgram *gProgram);
		void setTexture(const GLuint &id);
		void setAmbient(const glm::vec4 &ambient);
		void setDiffuse(const glm::vec4 &diffuse);
		void setSpecular(const glm::vec4 &specular);
		void setShininess(const GLfloat &shininess);
		GLfloat getTransparency(void);
		void load(const GLsizei &sizeVertexArray, const GLfloat *vertexArray,
			  const GLsizei &sizeIndexArray, const GLuint *indexArray);
		void display(GBuffer *g) const;
		void displayShadow(Light *l) const;
	};

	int comparGLObject(const void *p1, const void *p2);

}


#endif
