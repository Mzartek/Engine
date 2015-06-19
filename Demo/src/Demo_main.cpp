#include "Demo.hpp"

void Demo::display(GLfloat state)
{
	UNREFERENCED_PARAMETER(state);

	static Graphics::GraphicsRenderer &graphicsRenderer = Graphics::GraphicsRenderer::Instance();

	// Clear Buffers
	graphicsRenderer.clear();
	gbuffer->clear();

	nightBox->display(gbuffer, camera);

	// Opaque Object
	for (std::set<Graphics::Model *>::iterator it = object_display.begin(); it != object_display.end(); it++)
		(*it)->display(gbuffer, camera);

	for (GLuint i = 0; i < Graphics::DirLight::CASCADED_LEVEL; i++) depthMaps[i]->clear();
	for (std::set<Graphics::Model *>::iterator it = object_display.begin(); it != object_display.end(); it++)
		(*it)->displayDepthMaps(depthMaps, moon_light);
	moon_light->display(gbuffer, camera, depthMaps);

	depthMaps[0]->clear();
	for (std::set<Graphics::Model *>::iterator it = object_display.begin(); it != object_display.end(); it++)
		(*it)->displayDepthMap(depthMaps[0], torch_light);
	torch_light->display(gbuffer, camera, depthMaps[0]);

	gbuffer->background();

	// Transparent Object
	for (std::set<Graphics::Model *>::iterator it = object_display.begin(); it != object_display.end(); it++)
		(*it)->displayTransparent(gbuffer, camera);
	moon_light->display(gbuffer, camera);
	torch_light->display(gbuffer, camera);

	gbuffer->background();

	// Particles
	rain_particles->display(gbuffer, camera);
	smoke_particles->display(gbuffer, camera);

	graphicsRenderer.display(gbuffer->getIdTexture(Graphics::GBuffer::BACKGROUND_ID), glm::vec4(1, 1, 1, 1));
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
	moon_light->updateData(camPosition, 100, 250, 500);
	torch_light->updateData(depthMaps[0]);

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