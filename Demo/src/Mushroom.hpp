#ifndef MUSHROOM
#define MUSHROOM

#include <Engine/Model.hpp>

class Mushroom : public Engine::Model
{
private:
	Engine::ShaderProgram *_gProgram;
	Engine::ShaderProgram *_smProgram;
public:
	Mushroom(Engine::ShaderProgram *gProgram, Engine::ShaderProgram *smProgram, const GLchar *texture);
	Mushroom(Mushroom *mushroom);
	~Mushroom(void);
	virtual bool isCepe(void);
	virtual bool isPhalloide(void);
	virtual bool isSatan(void);
};

#endif