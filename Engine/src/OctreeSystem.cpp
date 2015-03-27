#include <Engine/OctreeSystem.hpp>
#include <Engine/Camera.hpp>
#include <Engine/Model.hpp>
#include <Engine/ParticlesManager.hpp>
#include <Engine/GBuffer.hpp>

// The Octree struct

struct Engine::Octree
{
	glm::vec3 position;
	glm::vec3 vertex[8];
	GLfloat dim;
	GLfloat dim_2;
	GLfloat radius;
	std::vector<Engine::Model *> modelContainer;
	struct Octree *next;
};

// Inline functions

static inline GLboolean checkCamInOctree(const Engine::Octree *octree, const Engine::Camera *cam)
{
	const glm::vec3 p = cam->getCameraPosition();

	if (p.x >= octree->vertex[0].x && p.x < octree->vertex[7].x &&
		p.y >= octree->vertex[0].y && p.y < octree->vertex[7].y &&
		p.z >= octree->vertex[0].z && p.z < octree->vertex[7].z)
		return GL_TRUE;
	return GL_FALSE;
}

static inline GLboolean checkOctreeInCamSphere(const Engine::Octree *octree, const Engine::Camera *cam)
{
	const glm::vec3 octree_position = cam->getCameraPosition();
	const GLfloat distance = glm::length(octree_position - cam->getFrusSpherePosition());

	if (distance < octree->radius + cam->getFrusSphereRadius())
		return GL_TRUE;
	return GL_FALSE;
}

static inline GLboolean checkOctreeInCamFrus(const Engine::Octree *octree, const Engine::Camera *cam)
{
	const glm::vec3 camera_position = cam->getCameraPosition();
	const glm::vec3 view_vector = cam->getViewVector();
	const GLfloat fov_2 = cam->getFOV() / 2;

	glm::vec3 position = octree->position;
	glm::vec3 direction = glm::normalize(position - camera_position);
	GLfloat dot = glm::dot(view_vector, direction);

	if (acosf(dot) < fov_2) return GL_TRUE;
	for (GLint i = 0; i < 8; i++)
	{
		position = octree->vertex[i];
		direction = glm::normalize(position - camera_position);
		dot = glm::dot(view_vector, direction);

		if (acosf(dot) < fov_2) return GL_TRUE;
	}
	return GL_FALSE;
}

// Private methods

void Engine::OctreeSystem::_initOctree(const GLuint &depth, Octree *octree, const glm::vec3 &position, const GLfloat &dim) const
{
	if (depth >= _maxDepth)	return;

	GLfloat newDim = dim / 2;
	GLfloat tmp = newDim / 2;

	octree->position = position;
	octree->dim = dim;
	octree->dim_2 = newDim;
	octree->radius = glm::length(glm::vec3(newDim));
	octree->next = new Octree[8];

	octree->vertex[0] = glm::vec3(position.x - newDim, position.y - newDim, position.z - newDim);
	octree->vertex[1] = glm::vec3(position.x - newDim, position.y - newDim, position.z + newDim);
	octree->vertex[2] = glm::vec3(position.x - newDim, position.y + newDim, position.z - newDim);
	octree->vertex[3] = glm::vec3(position.x - newDim, position.y + newDim, position.z + newDim);
	octree->vertex[4] = glm::vec3(position.x + newDim, position.y - newDim, position.z - newDim);
	octree->vertex[5] = glm::vec3(position.x + newDim, position.y - newDim, position.z + newDim);
	octree->vertex[6] = glm::vec3(position.x + newDim, position.y + newDim, position.z - newDim);
	octree->vertex[7] = glm::vec3(position.x + newDim, position.y + newDim, position.z + newDim);

	_initOctree(depth + 1, &octree->next[0], glm::vec3(position.x - tmp, position.y - tmp, position.z - tmp), newDim);
	_initOctree(depth + 1, &octree->next[1], glm::vec3(position.x - tmp, position.y - tmp, position.z + tmp), newDim);
	_initOctree(depth + 1, &octree->next[2], glm::vec3(position.x - tmp, position.y + tmp, position.z - tmp), newDim);
	_initOctree(depth + 1, &octree->next[3], glm::vec3(position.x - tmp, position.y + tmp, position.z + tmp), newDim);
	_initOctree(depth + 1, &octree->next[4], glm::vec3(position.x + tmp, position.y - tmp, position.z - tmp), newDim);
	_initOctree(depth + 1, &octree->next[5], glm::vec3(position.x + tmp, position.y - tmp, position.z + tmp), newDim);
	_initOctree(depth + 1, &octree->next[6], glm::vec3(position.x + tmp, position.y + tmp, position.z - tmp), newDim);
	_initOctree(depth + 1, &octree->next[7], glm::vec3(position.x + tmp, position.y + tmp, position.z + tmp), newDim);
}

void Engine::OctreeSystem::_destroyOctree(const GLuint &depth, Octree *octree) const
{
	if (depth >= _maxDepth)	return;

	for (GLuint i = 0; i < 8; i++)
		_destroyOctree(depth + 1, &(octree->next[i]));
	delete[] octree->next;
}

GLboolean Engine::OctreeSystem::_addModelOctree(const GLuint &depth, Octree *octree, Model *model, const GLfloat &dim) const
{
	if (depth >= _maxDepth) return GL_FALSE;
	if (dim > octree->dim) return GL_FALSE;

	glm::vec3 octree_pos = octree->position;
	glm::vec3 model_pos = model->getPosition();

	// Check the position
	if (model_pos.x < (octree_pos.x - octree->dim_2) || model_pos.x >= (octree_pos.x + octree->dim_2) ||
		model_pos.y < (octree_pos.y - octree->dim_2) || model_pos.y >= (octree_pos.y + octree->dim_2) ||
		model_pos.z < (octree_pos.z - octree->dim_2) || model_pos.z >= (octree_pos.z + octree->dim_2))
		return GL_FALSE;

	// Recursive call
	if (_addModelOctree(depth + 1, &octree->next[0], model, dim)) return GL_TRUE;
	if (_addModelOctree(depth + 1, &octree->next[1], model, dim)) return GL_TRUE;
	if (_addModelOctree(depth + 1, &octree->next[2], model, dim)) return GL_TRUE;
	if (_addModelOctree(depth + 1, &octree->next[3], model, dim)) return GL_TRUE;
	if (_addModelOctree(depth + 1, &octree->next[4], model, dim)) return GL_TRUE;
	if (_addModelOctree(depth + 1, &octree->next[5], model, dim)) return GL_TRUE;
	if (_addModelOctree(depth + 1, &octree->next[6], model, dim)) return GL_TRUE;
	if (_addModelOctree(depth + 1, &octree->next[7], model, dim)) return GL_TRUE;

	octree->modelContainer.push_back(model);

	return GL_TRUE;
}

void Engine::OctreeSystem::_removeModelOctree(const GLuint &depth, Octree *octree, Model *model) const
{
	if (depth >= _maxDepth) return;

	std::vector<Model *>::iterator iterator_begin = octree->modelContainer.begin();
	std::vector<Model *>::iterator iterator_end = octree->modelContainer.end();

	octree->modelContainer.erase(std::remove(iterator_begin, iterator_end, model), iterator_end);

	for (GLuint i = 0; i < 8; i++)
		_removeModelOctree(depth + 1, &(octree->next[i]), model);
}

void Engine::OctreeSystem::_getModelsOctree(const GLuint &depth, Octree *octree, GBuffer *gbuffer, Camera *cam, std::set<Model *> *modelSet) const
{
	if (depth >= _maxDepth)	return;

	if (!checkCamInOctree(octree, cam))
	{
		if (!checkOctreeInCamSphere(octree, cam)) return;
		if (!checkOctreeInCamFrus(octree, cam)) return;
	}
	
	modelSet->insert(octree->modelContainer.begin(), octree->modelContainer.end());

	for (GLuint i = 0; i < 8; i++)
		_getModelsOctree(depth + 1, &(octree->next[i]), gbuffer, cam, modelSet);
}

// Public methods

Engine::OctreeSystem::OctreeSystem(const GLuint &maxDepth, const glm::vec3 &pos, const GLfloat &dim)
{
	_maxDepth = maxDepth;
	_octree = new Octree;

	_initOctree(0, _octree, pos, dim);
}

Engine::OctreeSystem::~OctreeSystem()
{
	_destroyOctree(0, _octree);
	delete _octree;
}

void Engine::OctreeSystem::addModel(Model *model, const GLfloat &dim) const
{
	if (!_addModelOctree(0, _octree, model, dim))
		std::cerr << "Unable to add model on the OctreeSystem" << std::endl;
}

void Engine::OctreeSystem::removeModel(Model *model) const
{
	_removeModelOctree(0, _octree, model);
}

void Engine::OctreeSystem::getModels(GBuffer *gbuffer, Camera *cam, std::set<Model *> *modelSet) const
{
	_getModelsOctree(0, _octree, gbuffer, cam, modelSet);
}
