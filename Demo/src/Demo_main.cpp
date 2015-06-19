#include "Demo.hpp"

void Demo::display(GLfloat state)
{
	UNREFERENCED_PARAMETER(state);

	// Clear Buffers
	Graphics::GraphicsRenderer::Instance().clear();
	screenDisplay->getGBuffer()->clear();

	nightBox->display(screenDisplay->getGBuffer(), camera);

	// Opaque Object
	for (std::set<Graphics::Model *>::iterator it = object_display.begin(); it != object_display.end(); it++)
		(*it)->display(screenDisplay->getGBuffer(), camera);

	for (GLuint i = 0; i < Graphics::DirLight::CASCADED_LEVEL; i++) depthMaps[i]->clear();
	for (std::set<Graphics::Model *>::iterator it = object_display.begin(); it != object_display.end(); it++)
		(*it)->displayDepthMaps(depthMaps, moonLight->getLight());
	moonLight->getLight()->display(screenDisplay->getGBuffer(), camera, depthMaps);

	depthMaps[0]->clear();
	for (std::set<Graphics::Model *>::iterator it = object_display.begin(); it != object_display.end(); it++)
		(*it)->displayDepthMap(depthMaps[0], torchLight->getLight());
	torchLight->getLight()->display(screenDisplay->getGBuffer(), camera, depthMaps[0]);

	screenDisplay->getGBuffer()->background();

	// Transparent Object
	for (std::set<Graphics::Model *>::iterator it = object_display.begin(); it != object_display.end(); it++)
		(*it)->displayTransparent(screenDisplay->getGBuffer(), camera);
	moonLight->getLight()->display(screenDisplay->getGBuffer(), camera);
	torchLight->getLight()->display(screenDisplay->getGBuffer(), camera);

	screenDisplay->getGBuffer()->background();

	// Particles
	rainEffect->getParticlesHandler()->display(screenDisplay->getGBuffer(), camera);
	smokeEffect->getParticlesHandler()->display(screenDisplay->getGBuffer(), camera);

	Graphics::GraphicsRenderer::Instance().display(screenDisplay->getGBuffer()->getIdTexture(Graphics::GBuffer::BACKGROUND_ID), glm::vec4(1, 1, 1, 1));
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