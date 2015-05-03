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
		extern DLLAPI const aiScene *openFile(Assimp::Importer &importer, const GLchar *inFile);
		extern DLLAPI std::pair<std::vector<Engine::StaticMesh::Vertex>, std::vector<GLuint>> loadStaticVertices(const aiMesh *mesh);
		extern DLLAPI std::pair<std::vector<Engine::SkeletalMesh::Vertex>, std::vector<GLuint>> loadSkeletalVertices(const aiMesh *mesh, std::map<GLuint, GLuint> &map_vertex);
		extern DLLAPI Material *loadMaterial(const aiMaterial *material, const std::string &dir, std::set<Engine::Object *> *tObject);
		extern DLLAPI std::vector<glm::mat4> loadBones(const aiMesh *mesh,
			GLuint &bone_index, std::vector<Engine::SkeletalMesh::Vertex> &vertices, std::map<GLuint, GLuint> &map_vertex);
		extern DLLAPI Skeleton *loadSkeleton(const aiScene *scene, const GLchar *name, std::set<Object *> *tObject);
	}
}

#endif