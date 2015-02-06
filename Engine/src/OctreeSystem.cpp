#include <Engine/OctreeSystem.hpp>
#include <Engine/Camera.hpp>
#include <Engine/Model.hpp>
#include <Engine/ParticlesManager.hpp>
#include <Engine/GBuffer.hpp>

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
	if (glm::length(octree->position - cam->getFrusSpherePosition()) < octree->radius + cam->getFrusSphereRadius())
		return GL_TRUE;
	return GL_FALSE;
}

static inline GLboolean checkOctreeInCamFrus(const Engine::Octree *octree, const Engine::Camera *cam)
{
	const glm::vec3 p = cam->getCameraPosition();
	const glm::vec3 v = cam->getViewVector();
	const GLfloat fov_2 = cam->getFOV() / 2;

	if (acosf(glm::dot(v, glm::normalize(octree->position - p))) < fov_2) return GL_TRUE;
	for (GLint i = 0; i < 8; i++)
	{
		if (acosf(glm::dot(v, glm::normalize(octree->vertex[i] - p))) < fov_2) return GL_TRUE;
	}
	return GL_FALSE;
}

void Engine::OctreeSystem::initOctree(const GLuint &depth, Octree *octree, const glm::vec3 &position, const GLfloat &dim) const
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

	initOctree(depth + 1, &octree->next[0], glm::vec3(position.x - tmp, position.y - tmp, position.z - tmp), newDim);
	initOctree(depth + 1, &octree->next[1], glm::vec3(position.x - tmp, position.y - tmp, position.z + tmp), newDim);
	initOctree(depth + 1, &octree->next[2], glm::vec3(position.x - tmp, position.y + tmp, position.z - tmp), newDim);
	initOctree(depth + 1, &octree->next[3], glm::vec3(position.x - tmp, position.y + tmp, position.z + tmp), newDim);
	initOctree(depth + 1, &octree->next[4], glm::vec3(position.x + tmp, position.y - tmp, position.z - tmp), newDim);
	initOctree(depth + 1, &octree->next[5], glm::vec3(position.x + tmp, position.y - tmp, position.z + tmp), newDim);
	initOctree(depth + 1, &octree->next[6], glm::vec3(position.x + tmp, position.y + tmp, position.z - tmp), newDim);
	initOctree(depth + 1, &octree->next[7], glm::vec3(position.x + tmp, position.y + tmp, position.z + tmp), newDim);
}

void Engine::OctreeSystem::destroyOctree(const GLuint &depth, Octree *octree) const
{
	if (depth >= _maxDepth)	return;

	for (GLuint i = 0; i < 8; i++)
		destroyOctree(depth + 1, &(octree->next[i]));
	delete[] octree->next;
}

GLboolean Engine::OctreeSystem::addModelOctree(const GLuint &depth, Octree *octree, Model *model, const GLfloat &dim) const
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
	if (addModelOctree(depth + 1, &octree->next[0], model, dim)) return GL_TRUE;
	if (addModelOctree(depth + 1, &octree->next[1], model, dim)) return GL_TRUE;
	if (addModelOctree(depth + 1, &octree->next[2], model, dim)) return GL_TRUE;
	if (addModelOctree(depth + 1, &octree->next[3], model, dim)) return GL_TRUE;
	if (addModelOctree(depth + 1, &octree->next[4], model, dim)) return GL_TRUE;
	if (addModelOctree(depth + 1, &octree->next[5], model, dim)) return GL_TRUE;
	if (addModelOctree(depth + 1, &octree->next[6], model, dim)) return GL_TRUE;
	if (addModelOctree(depth + 1, &octree->next[7], model, dim)) return GL_TRUE;

	octree->modelContainer.push_back(model);

	return GL_TRUE;
}

void Engine::OctreeSystem::removeModelOctree(const GLuint &depth, Octree *octree, Model *model) const
{
	if (depth >= _maxDepth) return;

	GLuint i;

	for (i = 0; i < octree->modelContainer.size(); i++)
	{
		if (octree->modelContainer[i] == model)
			octree->modelContainer.erase(octree->modelContainer.begin() + i);
	}

	for (i = 0; i < 8; i++)
		removeModelOctree(depth + 1, &(octree->next[i]), model);
}

void Engine::OctreeSystem::getModelOctree(const GLuint &depth, Octree *octree, GBuffer *gbuffer, Camera *cam, std::vector<Model *> *modelVector) const
{
	if (depth >= _maxDepth)	return;

	if (!checkCamInOctree(octree, cam))
	{
		if (!checkOctreeInCamSphere(octree, cam)) return;
		if (!checkOctreeInCamFrus(octree, cam)) return;
	}

	GLuint i;

	for (i = 0; i < octree->modelContainer.size(); i++)
	{
		modelVector->push_back(octree->modelContainer[i]);
	}

	for (i = 0; i < 8; i++)
		getModelOctree(depth + 1, &(octree->next[i]), gbuffer, cam, modelVector);
}

Engine::OctreeSystem::OctreeSystem(const GLuint &maxDepth, const glm::vec3 &position, const GLfloat &dim)
{
	_maxDepth = maxDepth;
	_octree = new Octree;
	initOctree(0, _octree, position, dim);
}

Engine::OctreeSystem::~OctreeSystem()
{
	destroyOctree(0, _octree);
	delete _octree;
}

void Engine::OctreeSystem::addModel(Model *model, const GLfloat &dim) const
{
	if (!addModelOctree(0, _octree, model, dim))
		std::cerr << "Unable to add model on the OctreeSystem" << std::endl;
}

void Engine::OctreeSystem::removeModel(Model *model) const
{
	removeModelOctree(0, _octree, model);
}

void Engine::OctreeSystem::getModel(GBuffer *gbuffer, Camera *cam, std::vector<Model *> *modelVector) const
{
	getModelOctree(0, _octree, gbuffer, cam, modelVector);
}