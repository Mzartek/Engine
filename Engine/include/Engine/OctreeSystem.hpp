#ifndef OCTREESYSTEM_HEADER
#define OCTREESYSTEM_HEADER

#include "Object.hpp"

namespace Engine
{
	class PerspCamera;
	class Model;
	class ParticlesManager;
	class GBuffer;

	struct Octree;

	class DLLAPI OctreeSystem : public Object
	{
	private:
		GLuint _maxDepth;
		Octree *_octree;
		void _initOctree(const GLuint &depth, Octree *octree, const glm::vec3 &position, const GLfloat &dim) const;
		void _destroyOctree(const GLuint &depth, Octree *octree) const;
		GLboolean _addModelOctree(const GLuint &depth, Octree *octree, Model *model, const GLfloat &dim) const;
		void _removeModelOctree(const GLuint &depth, Octree *octree, Model *model) const;
		void _getModelsOctree(const GLuint &depth, Octree *octree, GBuffer *gbuffer, PerspCamera *cam, std::set<Model *> *modelSet) const;
	public:
		OctreeSystem(const GLuint &maxDepth, const glm::vec3 &pos, const GLfloat &dim);
		~OctreeSystem(void);
		void addModel(Model *model, const GLfloat &dim) const;
		void removeModel(Model *model) const;
		void getModels(GBuffer *gbuffer, PerspCamera *cam, std::set<Model *> *modelSet) const;
	};
}

#endif