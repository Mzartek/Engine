#include "Ground.hpp"

Ground::Ground(void)
{
	_objectProgram = std::shared_ptr<Engine::ShaderProgram>(new Engine::ShaderProgram(
		"../share/Demo/shader/object/objectVert.glsl",
		NULL,
		NULL,
		"../share/Demo/shader/object/objectGeom.glsl",
		"../share/Demo/shader/object/objectFrag.glsl"));

	_depthMapProgram = std::shared_ptr<Engine::ShaderProgram>(new Engine::ShaderProgram(
		"../share/Demo/shader/depthMap/depthMapVert.glsl",
		NULL,
		NULL,
		NULL,
		"../share/Demo/shader/depthMap/depthMapFrag.glsl"));

	_texture = std::shared_ptr<Engine::Texture2D>(new Engine::Texture2D);
	_material = std::shared_ptr<Engine::Material>(new Engine::Material);
	_mesh = std::shared_ptr<Engine::StaticMesh>(new Engine::StaticMesh);
	_model = std::shared_ptr<Engine::StaticModel>(new Engine::StaticModel(_objectProgram, _depthMapProgram));

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
}

const std::shared_ptr<Engine::StaticModel> &Ground::getModel(void) const
{
	return _model;
}
