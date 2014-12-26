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
	GLfloat radius;
	std::vector<Engine::Model *> modelContainer;
	//std::vector<Engine::ParticlesManager *> particlesContainer;
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
	if (glm::length(octree->position - cam->getCameraPosition()) < octree->radius + cam->getFrusSphereRadius())
		return GL_TRUE;
	return GL_FALSE;
}

static inline GLboolean checkOctreeInCamFrus(const Engine::Octree *octree, const Engine::Camera *cam)
{
	const glm::vec3 p = cam->getCameraPosition();
	const glm::vec3 v = cam->getViewVector();
	const GLfloat FOV = cam->getFOV();

	if (acos(glm::dot(v, glm::normalize(octree->position - p))) < FOV / 2) return GL_TRUE;
	for (GLint i = 0; i < 8; i++)
	{
		if (acos(glm::dot(v, glm::normalize(octree->vertex[i] - p))) < FOV / 2)	return GL_TRUE;
	}
	return GL_FALSE;
}

void Engine::OctreeSystem::initOctree(const GLuint &depth, Octree *octree, const glm::vec3 &position, const GLfloat &dim)
{
	if (depth >= _maxDepth)	return;

	GLfloat newDim = dim / 2;
	GLfloat tmp = newDim / 2;

	octree->position = position;
	octree->dim = dim;
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

void Engine::OctreeSystem::destroyOctree(const GLuint &depth, Octree *octree)
{
	if (depth >= _maxDepth)	return;

	for (GLuint i = 0; i < 8; i++)
		destroyOctree(depth + 1, &(octree->next[i]));
	delete[] octree->next;
}

GLboolean Engine::OctreeSystem::addOctreeModel(const GLuint &depth, Octree *octree, Model *model, const GLfloat &dim)
{
	if (depth >= _maxDepth || dim > octree->dim) return GL_FALSE;

	glm::vec3 octree_pos = octree->position;
	glm::vec3 model_pos = model->getPosition();

	// Check the position
	if (model_pos.x < (octree_pos.x - octree->dim) || model_pos.y >= (octree_pos.x + octree->dim) ||
		model_pos.y < (octree_pos.y - octree->dim) || model_pos.y >= (octree_pos.y + octree->dim) ||
		model_pos.z < (octree_pos.z - octree->dim) || model_pos.z >= (octree_pos.z + octree->dim)) 
		return GL_FALSE;

	// Recursive call
	if (addOctreeModel(depth + 1, &octree->next[0], model, dim)) return GL_TRUE;
	if (addOctreeModel(depth + 1, &octree->next[1], model, dim)) return GL_TRUE;
	if (addOctreeModel(depth + 1, &octree->next[2], model, dim)) return GL_TRUE;
	if (addOctreeModel(depth + 1, &octree->next[3], model, dim)) return GL_TRUE;
	if (addOctreeModel(depth + 1, &octree->next[4], model, dim)) return GL_TRUE;
	if (addOctreeModel(depth + 1, &octree->next[5], model, dim)) return GL_TRUE;
	if (addOctreeModel(depth + 1, &octree->next[6], model, dim)) return GL_TRUE;
	if (addOctreeModel(depth + 1, &octree->next[7], model, dim)) return GL_TRUE;

	octree->modelContainer.push_back(model);

	return GL_TRUE;
}

/*GLboolean Engine::OctreeSystem::addOctreeParticles(const GLuint &depth, Octree *octree, ParticlesManager *particles, const GLfloat &dim)
{
	if (depth >= _maxDepth || dim > octree->dim) return GL_FALSE;

	glm::vec3 octree_pos = octree->position;
	glm::vec3 particles_pos = particles->getPosition();

	// Check the position
	if (particles_pos.x < (octree_pos.x - octree->dim) || particles_pos.y >= (octree_pos.x + octree->dim) ||
		particles_pos.y < (octree_pos.y - octree->dim) || particles_pos.y >= (octree_pos.y + octree->dim) ||
		particles_pos.z < (octree_pos.z - octree->dim) || particles_pos.z >= (octree_pos.z + octree->dim))
		return GL_FALSE;

	// Recursive call
	if (addOctreeParticles(depth + 1, &octree->next[0], particles, dim)) return GL_TRUE;
	if (addOctreeParticles(depth + 1, &octree->next[1], particles, dim)) return GL_TRUE;
	if (addOctreeParticles(depth + 1, &octree->next[2], particles, dim)) return GL_TRUE;
	if (addOctreeParticles(depth + 1, &octree->next[3], particles, dim)) return GL_TRUE;
	if (addOctreeParticles(depth + 1, &octree->next[4], particles, dim)) return GL_TRUE;
	if (addOctreeParticles(depth + 1, &octree->next[5], particles, dim)) return GL_TRUE;
	if (addOctreeParticles(depth + 1, &octree->next[6], particles, dim)) return GL_TRUE;
	if (addOctreeParticles(depth + 1, &octree->next[7], particles, dim)) return GL_TRUE;

	octree->particlesContainer.push_back(particles);

	return GL_TRUE;
}*/

void Engine::OctreeSystem::displayOctree(const GLuint &depth, Octree *octree, GBuffer *gbuffer, Camera *cam)
{
	if (depth >= _maxDepth)	return;

	if (!checkCamInOctree(octree, cam))
	{
		if (!checkOctreeInCamSphere(octree, cam)) return;
		if (!checkOctreeInCamFrus(octree, cam)) return;
	}

	for (GLuint i = 0; i < octree->modelContainer.size(); i++)
	{
		octree->modelContainer[i]->display(gbuffer, cam);
	}

	for (GLuint i = 0; i < 8; i++)
		displayOctree(depth + 1, &(octree->next[i]), gbuffer, cam);
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

void Engine::OctreeSystem::addModel(Model *model, const GLfloat &dim)
{
	if (!addOctreeModel(0, _octree, model, dim))
		std::cerr << "Unable to add model on the OctreeSystem" << std::endl;
}

/*void Engine::OctreeSystem::addParticles(ParticlesManager *particles, const GLfloat &dim)
{
	if (!addOctreeParticles(0, _octree, particles, dim))
		std::cerr << "Unable to add particles on the OctreeSystem" << std::endl;
}*/

void Engine::OctreeSystem::display(GBuffer *gbuffer, Camera *cam)
{
	displayOctree(0, _octree, gbuffer, cam);
}