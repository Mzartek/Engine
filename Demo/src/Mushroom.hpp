#ifndef MUSHROOM
#define MUSHROOM

#define MUSHROOM_NONE 0
#define MUSHROOM_CEPE 1
#define MUSHROOM_PHALLOIDE 2
#define MUSHROOM_SATAN 3

#include <Engine/Model.hpp>

class Mushroom : public Engine::Model
{
private:
	Engine::ShaderProgram *_gProgram;
	Engine::ShaderProgram *_smProgram;
protected:
	GLuint _type;
	bool _eaten;
public:
	Mushroom(Engine::ShaderProgram *gProgram, Engine::ShaderProgram *smProgram, const GLchar *texture);
	Mushroom(Mushroom *mushroom);
	~Mushroom(void);
	void eat(void);
	bool isCepe(void);
	bool isPhalloide(void);
	bool isSatan(void);
	bool isEaten(void);
};

#endif