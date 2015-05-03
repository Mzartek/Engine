#ifndef MESH_HEADER
#define MESH_HEADER

#include "../Object.hpp"
#include "../Tools/ControllerMemory.hpp"

#include "TextureCube.hpp"
#include "Buffer.hpp"
#include "Material.hpp"

namespace Engine
{
	enum MeshType {STATIC_MESH, SKELETAL_MESH};

	class DLLAPI Mesh : public Object
	{
		friend struct CompareMesh;

	private:
		Material *_material;
		GLuint _tex[10];

	protected:
		Buffer *_vertexBuffer;
		Buffer *_indexBuffer;
		GLuint _idVAO;
		GLsizei _numElement;

	public:
		Mesh(void);
		~Mesh(void);
		void setMaterial(Material *material);
		Material *getMaterial(void) const;
		void display(void) const;
		void display(TextureCube *cubeTexture) const;
		void displayShadow(void) const;

		virtual MeshType getType(void) const = 0;
	};

	struct CompareMesh
	{
		bool operator() (const Mesh *first, const Mesh *second);
	};
}


#endif
