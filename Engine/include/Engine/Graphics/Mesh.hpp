#ifndef MESH_HEADER
#define MESH_HEADER

#include "../Object.hpp"

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
		std::shared_ptr<Material> _material;
		GLuint _tex[10];

	protected:
		std::shared_ptr<Buffer> _vertexBuffer;
		std::shared_ptr<Buffer> _indexBuffer;
		GLuint _idVAO;
		GLsizei _numElement;

	public:
		Mesh(void);
		~Mesh(void);
		void setMaterial(const std::shared_ptr<Material> &material);
		const std::shared_ptr<Material> &getMaterial(void) const;
		void display(void) const;
		void display(const std::shared_ptr<TextureCube> &cubeTexture) const;
		void displayShadow(void) const;

		virtual MeshType getType(void) const = 0;
	};

	struct CompareMesh
	{
		bool operator() (const std::shared_ptr<Mesh> &first, const std::shared_ptr<Mesh> &second);
	};
}


#endif
