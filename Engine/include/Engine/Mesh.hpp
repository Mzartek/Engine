#ifndef MESH_HEADER
#define MESH_HEADER

#include "Object.hpp"

namespace Engine
{
	class Texture2D;
	class TextureCube;
	class Buffer;
	class Material;

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
		Buffer *_vertexBuffer;
		Buffer *_indexBuffer;
		GLuint _idVAO;
		GLsizei _numElement;

		Material *_material;
		GLuint _tex[10];
	public:
		Mesh(void);
		~Mesh(void);
		void setMaterial(Material *material);
		Material *getMaterial(void) const;
		void load(const GLsizei &numVertex, const Vertex *vertexArray,
			const GLsizei &numIndex, const GLuint *indexArray);
		void display(void) const;
		void display(TextureCube *cubeTexture) const;
		void displayShadow(void) const;
	};

	struct CompareMesh
	{
		bool operator() (const Mesh *first, const Mesh *second);
	};
}


#endif
