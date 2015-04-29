#ifndef ARMYSOLDIER_HEADER
#define ARMYSOLDIER_HEADER

#include <Engine/Engine.hpp>

class ArmySoldier
{
private:
	Engine::ShaderProgram *_objectProgram;
	Engine::ShaderProgram *_depthMapProgram;
	Engine::StaticModel *_model;
public:
	ArmySoldier(void);
	~ArmySoldier(void);
	Engine::StaticModel *getModel(void) const;
};

#endif