#ifndef CONFIG
#define CONFIG

#define ESC 41
#define MAJ 225

#include <Engine/Renderer.hpp>
#include <Engine/Object.hpp>
#include <Engine/ShaderProgram.hpp>
#include <Engine/ShadowMap.hpp>
#include <Engine/FreeCam.hpp>
#include <Engine/DirLight.hpp>
#include <Engine/Model.hpp>
#include <Engine/SkyBox.hpp>
#include <Engine/Screen.hpp>
#include <Engine/TextArray.hpp>
#include <Engine/GBuffer.hpp>

extern GLboolean keyState[256];
extern GLfloat sr, sg, sb, sa;

extern engine::Renderer *renderer;
extern engine::FreeCam *cam;
extern engine::DirLight *sun;
extern engine::Model *face;
extern engine::Model *cube1;
extern engine::Model *cube2;
extern engine::Model *cube3;
extern engine::Model *cube4;
extern engine::Model *heli;
extern engine::SkyBox *skybox;
extern engine::Screen *screen;
extern engine::TextArray *text1;
extern engine::TextArray *text2;
extern engine::TextArray *text3;
extern engine::GBuffer *gBuffer;

extern engine::ShaderProgram *objectProgram;
extern engine::ShaderProgram *lightProgram;
extern engine::ShaderProgram *shadowProgram;
extern engine::ShaderProgram *skyboxProgram;
extern engine::ShaderProgram *screenProgram;
extern engine::ShaderProgram *textProgram;

extern void configShaders(void);
extern void configBuffers(void);
extern void configText(void);
extern void configLights(void);
extern void configScreen(void);
extern void configModels(void);
extern void configSkybox(void);

#endif
