#ifndef ASSIMPTOOL_HEADER
#define ASSIMPTOOL_HEADER

#include <Engine/Object.hpp>
#include <Engine/Tools/ControllerMemory.hpp>

#include <Engine/Graphics/StaticMesh.hpp>
#include <Engine/Graphics/SkeletalMesh.hpp>
#include <Engine/Graphics/Material.hpp>
#include <Engine/Graphics/Texture2D.hpp>

#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#include "Skeleton.hpp"

namespace Engine
{
	namespace AssimpTool
	{
		extern const aiScene *openFile(Assimp::Importer &importer, const GLchar *inFile);
		extern std::vector<Engine::StaticMesh::Vertex> loadStaticVertices(const aiMesh *mesh);
		extern std::vector<Engine::SkeletalMesh::Vertex> loadSkeletalVertices(const aiMesh *mesh, std::map<GLuint, GLuint> &map_vertex);
		extern std::vector<GLuint> loadIndices(const aiMesh *mesh);
		extern Material *loadMaterial(const aiMaterial *material, const std::string &dir, std::set<Engine::Object *> *tObject);
		extern Skeleton *loadSkeleton(const aiScene *scene, const GLchar *name, std::set<Object *> *tObject);
		extern std::vector<Engine::Bone *> loadBones(const aiMesh *mesh, Skeleton *skeleton, GLuint &bone_index, 
			std::vector<Engine::SkeletalMesh::Vertex> &vertices, std::map<GLuint, GLuint> &map_vertex, 
			std::set<Object *> *tObject);
	}
}

#endif