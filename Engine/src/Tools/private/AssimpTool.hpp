#ifndef ASSIMPTOOL_HEADER
#define ASSIMPTOOL_HEADER

#include <Engine/Object.hpp>

#include <Engine/Graphics/StaticMesh.hpp>
#include <Engine/Graphics/SkeletalMesh.hpp>
#include <Engine/Graphics/Material.hpp>
#include <Engine/Graphics/Texture2D.hpp>
#include <Engine/Graphics/Skeleton.hpp>

#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

namespace Engine
{
	namespace ToolsPrivate
	{
		extern const aiScene *openFile(Assimp::Importer &importer, const GLchar *inFile);
		extern std::vector<Graphics::StaticMesh::Vertex> loadStaticVertices(const aiMesh *mesh);
		extern std::vector<Graphics::SkeletalMesh::Vertex> loadSkeletalVertices(const aiMesh *mesh, std::map<GLuint, GLuint> &map_vertex);
		extern std::vector<GLuint> loadIndices(const aiMesh *mesh);
		extern std::shared_ptr<Graphics::Material> loadMaterial(const aiMaterial *material, const std::string &dir);
		extern std::shared_ptr<Graphics::Skeleton> loadSkeleton(const aiScene *scene, const GLchar *name);
		extern std::vector<std::shared_ptr<Graphics::Bone>> loadBones(const aiMesh *mesh, const std::shared_ptr<Graphics::Skeleton> &skeleton, GLuint bone_index, 
			std::vector<Graphics::SkeletalMesh::Vertex> &vertices, std::map<GLuint, GLuint> &map_vertex);
	}
}

#endif