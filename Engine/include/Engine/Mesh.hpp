#ifndef MESH_HEADER
#define MESH_HEADER

#include "Object.hpp"

namespace Engine
{
	class Texture;
	class Buffer;

	struct Vertex
	{
		glm::vec3 position;
		glm::vec2 texCoord;
		glm::vec3 normal;
		glm::vec3 tangent;
	};

	class DLLAPI Mesh : public Object
	{
		friend struct CompareMesh;

	private:
		struct material
		{
			glm::vec4 ambient;
			glm::vec4 diffuse;
			glm::vec4 specular;
			GLfloat ALIGN(16) shininess;
		} _material;

		Texture *_colorTexture;
		Texture *_NMTexture;
		Buffer *_vertexBuffer;
		Buffer *_indexBuffer;
		Buffer *_materialBuffer;
		GLuint _idVAO;
		GLsizei _numElement;
	public:
		Mesh(void);
		~Mesh(void);
		void setColorTexture(const GLchar *path) const;
		void setNMTexture(const GLchar *path) const;
		void setAmbient(const glm::vec4 &ambient);
		void setDiffuse(const glm::vec4 &diffuse);
		void setSpecular(const glm::vec4 &specular);
		void setShininess(const GLfloat &shininess);
		GLfloat getTransparency(void) const;
		void load(const GLsizei &numVertex, const Vertex *vertexArray,
			const GLsizei &numIndex, const GLuint *indexArray);
		void display(void) const;
		void display(Texture *cubeTexture) const;
		void displayShadow(void) const;
	};

	struct CompareMesh
	{
		bool operator() (const Mesh *first, const Mesh *second);
	};
}


#endif
