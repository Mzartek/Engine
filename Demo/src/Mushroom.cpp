#include "Mushroom.hpp"

Mushroom::Mushroom(Engine::ShaderProgram *gProgram, Engine::ShaderProgram *smProgram, const GLchar *texture)
	: Model(gProgram, smProgram), _type(MUSHROOM_NONE)
{
	_gProgram = gProgram;
	_smProgram = smProgram;
	GLfloat vertexArray[] =
	{
		-1.0f, -1.5f, 0, 0, 0, 0, 0, 1, 0, 1, 0,
		-1.0f, 1.5f, 0, 0, 1, 0, 0, 1, 0, 1, 0,
		1.0f, 1.5f, 0, 1, 1, 0, 0, 1, 0, 1, 0,
		1.0f, -1.5f, 0, 1, 0, 0, 0, 1, 0, 1, 0
	};
	GLuint index[] = { 2, 0, 1, 0, 2, 3 };
	glm::vec4 mat_ambient(0.2f, 0.2f, 0.2f, 1.0f);
	glm::vec4 mat_diffuse(0.9f, 0.9f, 0.9f, 1.0f);
	glm::vec4 mat_specular(1.0f, 1.0f, 1.0f, 1.0f);
	GLfloat mat_shininess = 20.0f;

	this->initMeshArray();
	this->addMesh(sizeof vertexArray, vertexArray, sizeof index, index, texture, "resources/NM_none.png", mat_ambient, mat_diffuse, mat_specular, mat_shininess);
}

Mushroom::Mushroom(Mushroom *mushroom)
	: Model(mushroom->_gProgram, mushroom->_smProgram), _type(MUSHROOM_NONE)
{
	this->initMeshMirror(mushroom);
}

Mushroom::~Mushroom(void)
{
}

bool Mushroom::isCepe(void)
{
	return (_type == MUSHROOM_CEPE) ? true : false;
}

bool Mushroom::isPhalloide(void)
{
	return (_type == MUSHROOM_PHALLOIDE) ? true : false;
}

bool Mushroom::isSatan(void)
{
	return (_type == MUSHROOM_SATAN) ? true : false;
}