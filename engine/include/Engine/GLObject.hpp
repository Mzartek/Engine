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
		GLuint _idColorTexture;
		GLuint _idNMTexture;
		GLuint _idVAO;
		GLuint _idVBO;
		GLuint _idIBO;
		GLuint _idMaterialBuffer;
		struct material
		{
			glm::vec4 ambient;
			glm::vec4 diffuse;
			glm::vec4 specular;
			GLfloat ALIGN(16) shininess;
		} _material;
		GLsizei _numElement;
	public:
		GLObject(void);
		~GLObject(void);
		void setColorTexture(const GLuint &id);
		void setNMTexture(const GLuint &id);
		void setAmbient(const glm::vec4 &ambient);
		void setDiffuse(const glm::vec4 &diffuse);
		void setSpecular(const glm::vec4 &specular);
		void setShininess(const GLfloat &shininess);
		GLfloat getTransparency(void);
		void load(const GLsizei &sizeVertexArray, const GLfloat *vertexArray,
			  const GLsizei &sizeIndexArray, const GLuint *indexArray);
		void display(const GLint &colorTextureLocation, const GLint &nmTextureLocation, const GLuint &materialBlockIndex) const;
		void displayShadow(const GLint &colorLocation) const;
	};

	int comparGLObject(const void *p1, const void *p2);

}


#endif
