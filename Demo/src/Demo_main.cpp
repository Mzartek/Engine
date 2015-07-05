#include "Demo.hpp"

void Demo::display(GLfloat state)
{
	UNREFERENCED_PARAMETER(state);

	// Clear Buffers
	Graphics::GraphicsRenderer::Instance().clear();
	gbuffer->clear();

	nightBox->display(gbuffer, camera);

	// Opaque Object
	for (std::set<Graphics::Model *>::iterator it = object_display.begin(); it != object_display.end(); it++)
		(*it)->display(gbuffer, camera);

	for (GLuint i = 0; i < Graphics::DirLight::CASCADED_LEVEL; i++) depthMaps[i]->clear();
	for (std::set<Graphics::Model *>::iterator it = object_display.begin(); it != object_display.end(); it++)
		(*it)->displayDepthMaps(depthMaps, moonLight->getLight());
	moonLight->getLight()->display(gbuffer, camera, depthMaps);

	depthMaps[0]->clear();
	for (std::set<Graphics::Model *>::iterator it = object_display.begin(); it != object_display.end(); it++)
		(*it)->displayDepthMap(depthMaps[0], torchLight->getLight());
	torchLight->getLight()->display(gbuffer, camera, depthMaps[0]);

	Graphics::Screen::Instance().displayGBufferBackground(gbuffer, backgroundProgram);

	// Transparent Object
	for (std::set<Graphics::Model *>::iterator it = object_display.begin(); it != object_display.end(); it++)
		(*it)->displayTransparent(gbuffer, camera);
	moonLight->getLight()->display(gbuffer, camera);
	torchLight->getLight()->display(gbuffer, camera);

	Graphics::Screen::Instance().displayGBufferBackground(gbuffer, backgroundProgram);

	// Particles
	rainEffect->getParticlesHandler()->display(gbuffer, camera);
	smokeEffect->getParticlesHandler()->display(gbuffer, camera);

	bloomPost->applyFilter(gbuffer);

	Graphics::Screen::Instance().displayOnScreen(bloomPost->getCBuffer(), glm::vec4(1, 1, 1, 1), windowProgram);
}

void Demo::state(long long time)
{
	const glm::vec3 &camPosition = camera->getCameraPosition();

	this->manage_input();

	rainEffect->setPosition(camPosition);

	rainEffect->updateParticles();
	smokeEffect->updateParticles();
}

void Demo::last_state(void)
{
	const glm::vec3 &camPosition = camera->getCameraPosition();
	const glm::vec3 &camForward = camera->getForwardVector();
	const glm::vec3 &camUp = camera->getUpVector();

	camera->updateData();
	moonLight->getLight()->updateData(camPosition, 100, 250, 500);
	torchLight->getLight()->updateData(depthMaps[0]);

	// We retrieve object to display from the octree
	object_display.clear();

	octree->getModels(camera, object_display);

	Audio::AudioRenderer::Instance().setListenerPosition(camPosition, camForward, camUp);
}

void Demo::reshape(GLuint w, GLuint h)
{
	camera->setPerspective(glm::pi<GLfloat>() / 2, w, h, 0.1f, 1000.0f);
}

void Demo::launch(void)
{
	Graphics::GraphicsRenderer::Instance().mainLoop(this);
}