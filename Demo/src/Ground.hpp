#ifndef GROUND_HEADER
#define GROUND_HEADER

#include <Engine/Graphics/ShaderProgram.hpp>
#include <Engine/Graphics/StaticModel.hpp>

class Ground
{
private:
	Engine::ShaderProgram *_objectProgram;
	Engine::ShaderProgram *_depthMapProgram;
	Engine::Texture2D *_texture;
	Engine::Material *_material;
	Engine::StaticMesh *_mesh;
	Engine::StaticModel *_model;
public:
	Ground(void);
	~Ground(void);
	Engine::StaticModel *getModel(void) const;
};

#endif
