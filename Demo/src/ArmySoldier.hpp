#ifndef ARMYSOLDIER_HEADER
#define ARMYSOLDIER_HEADER

#include <Engine/Engine.hpp>

class ArmySoldier
{
private:
	Engine::ShaderProgram *_objectProgram;
	Engine::ShaderProgram *_depthMapProgram;
	Engine::SkeletalModel *_model;
public:
	ArmySoldier(void);
	~ArmySoldier(void);
	Engine::SkeletalModel *getModel(void) const;
};

#endif