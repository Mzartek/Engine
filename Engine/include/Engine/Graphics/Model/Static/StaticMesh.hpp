#ifndef STATICMESH_HEADER
#define STATICMESH_HEADER

#include "../Mesh.hpp"

namespace Engine
{
	namespace Graphics
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
			void load(GLsizei numVertex, const Vertex *vertexArray, GLsizei numIndex, const GLuint *indexArray);
			void load(const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices);

			MeshType getType(void) const;
		};
	}
}

#endif