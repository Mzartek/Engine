#ifndef MESH
#define MESH

#include "Object.hpp"

namespace engine
{
	class Texture;
	class Buffer;

	class DLLAPI Mesh : public Object
	{
		friend int comparMesh(const void *p1, const void *p2);

	private:
		Texture *_colorTexture;
		Texture *_NMTexture;
		GLuint _idVAO;
		Buffer *_vertexBuffer;
		Buffer *_indexBuffer;
		Buffer *_materialBuffer;
		struct material
		{
			glm::vec4 ambient;
			glm::vec4 diffuse;
			glm::vec4 specular;
			GLfloat ALIGN(16) shininess;
		} _material;
		GLsizei _numElement;
	public:
		Mesh(void);
		~Mesh(void);
		void setColorTexture(const GLchar *path);
		void setNMTexture(const GLchar *path);
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

	int comparMesh(const void *p1, const void *p2);

}


#endif
