#include "Ground.hpp"

Ground::Ground(void)
{
	_objectProgram = new_ptr(Engine::ShaderProgram(
		"../share/Demo/shader/object/objectVert.glsl",
		NULL,
		NULL,
		"../share/Demo/shader/object/objectGeom.glsl",
		"../share/Demo/shader/object/objectFrag.glsl"));

	_depthMapProgram = new_ptr(Engine::ShaderProgram(
		"../share/Demo/shader/depthMap/depthMapVert.glsl",
		NULL,
		NULL,
		NULL,
		"../share/Demo/shader/depthMap/depthMapFrag.glsl"));

	_texture = new_ptr(Engine::Texture2D);
	_material = new_ptr(Engine::Material);
	_mesh = new_ptr(Engine::StaticMesh);
	_model = new_ptr(Engine::StaticModel(_objectProgram, _depthMapProgram));

	_texture->loadFromFile("../share/Demo/resources/textures/feuilles.png");
	_material->setDiffuseTexture(_texture);
	_material->setAmbient(glm::vec3(0.5f, 0.5f, 0.5f));
	_material->setDiffuse(glm::vec3(0.9f, 0.9f, 0.9f));
	_material->setSpecular(glm::vec3(1.0f, 1.0f, 1.0f));
	_material->setOpacity(1.0f);
	_material->setShininess(20.0f);

	Engine::StaticMesh::Vertex vertexArray[] =
	{
		glm::vec3(-500, 0, -500), glm::vec2(0, 0), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0),
		glm::vec3(-500, 0, 500), glm::vec2(0, 25), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0),
		glm::vec3(500, 0, 500), glm::vec2(25, 25), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0),
		glm::vec3(500, 0, -500), glm::vec2(25, 0), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0),
	};
	GLuint index[] = { 2, 0, 1, 0, 2, 3 };

	_mesh->setMaterial(_material);
	_mesh->load(sizeof vertexArray / sizeof(Engine::StaticMesh::Vertex), vertexArray, sizeof index / sizeof(GLuint), index);

	_model->addMesh(_mesh);
}

Ground::~Ground(void)
{
	release_ptr(_objectProgram);
	release_ptr(_depthMapProgram);
	release_ptr(_texture);
	release_ptr(_material);
	release_ptr(_mesh);
	release_ptr(_model);
}

Engine::StaticModel *Ground::getModel(void) const
{
	return _model;
}
