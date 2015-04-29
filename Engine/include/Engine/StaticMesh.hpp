#ifndef STATICMESH_HEADER
#define STATICMESH_HEADER

#include "Mesh.hpp"

namespace Engine
{
	class DLLAPI StaticMesh : public Mesh
	{
	public:
		struct Vertex
		{
			glm::vec3 position;
			glm::vec2 texCoord;
			glm::vec3 normal;
			glm::vec3 tangent;
		};

		StaticMesh(void);
		~StaticMesh(void);
		void load(const GLsizei &numVertex, const Vertex *vertexArray,
			const GLsizei &numIndex, const GLuint *indexArray);

		MeshType getType(void) const;
	};
}

#endif