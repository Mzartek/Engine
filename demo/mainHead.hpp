#ifndef SEQUENCE
#define SEQUENCE

#define ESC 41
#define MAJ 225

#include <Engine/Window.hpp>
#include <Engine/ShaderProgram.hpp>
#include <Engine/ShadowMap.hpp>
#include <Engine/FreeCam.hpp>
#include <Engine/DirLight.hpp>
#include <Engine/OBJModel.hpp>
#include <Engine/SkyBox.hpp>
#include <Engine/Screen.hpp>
#include <Engine/TextArray.hpp>
#include <Engine/GBuffer.hpp>
#include <SDL2/SDL_mixer.h>

extern GLboolean keyState[256];
extern Mix_Music *song;
extern GLfloat sr, sg, sb, sa;

extern engine::Window *window;
extern engine::Camera *cam;
// extern engine::FreeCam *cam;
extern engine::DirLight *sun;
extern engine::Model *face;
extern engine::OBJModel *helicopter;
extern engine::OBJModel *grotor;
extern engine::OBJModel *protor;
extern engine::SkyBox *sky;
extern engine::TextArray *text1;
extern engine::TextArray *text2;
extern engine::TextArray *text3;

extern engine::ShaderProgram *mainProgram;
extern engine::ShaderProgram *shadowProgram;
extern engine::ShaderProgram *skyboxProgram;
extern engine::ShaderProgram *textProgram;

extern void helicopterMatrixIdentity(void);
extern void helicopterMatrixScale(GLfloat x, GLfloat y, GLfloat z);
extern void helicopterMatrixTranslate(GLfloat x, GLfloat y, GLfloat z);
extern void helicopterMatrixRotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
extern void helicopterRotateRotor(GLfloat angle);

extern void sequence(void);

#endif
