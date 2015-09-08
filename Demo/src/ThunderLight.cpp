#include "ThunderLight.hpp"

ThunderLight::ThunderLight(void)
{
	_dirLightProgram = std::make_shared<Graphics::ShaderProgram>(
		"../share/Demo/shader/dirLight/dirLightVert.glsl",
		nullptr,
		nullptr,
		nullptr,
		"../share/Demo/shader/dirLight/dirLightFrag.glsl");

	_light = std::make_shared<Graphics::DirLight>(_dirLightProgram);

	_light->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
	_light->setDirection(glm::vec3(static_cast<GLfloat>(rand()) / RAND_MAX, -1.0f, static_cast<GLfloat>(rand()) / RAND_MAX));

	for (GLuint i = 0; i < 4; i++)
	{
		_sound[i] = std::make_shared<Audio::Sound>();
		_sound[i]->setGain(1.0f);
		_sound[i]->setPitch(1.0f);
		_sound[i]->setLoop(AL_FALSE);
	}
	_sound[0]->loadFromFile("../share/Demo/resources/sound/thunder0_stereo.wav", 44100, AL_FORMAT_STEREO16);
	_sound[1]->loadFromFile("../share/Demo/resources/sound/thunder1_stereo.wav", 44100, AL_FORMAT_STEREO16);
	_sound[2]->loadFromFile("../share/Demo/resources/sound/thunder2_stereo.wav", 44100, AL_FORMAT_STEREO16);
	_sound[3]->loadFromFile("../share/Demo/resources/sound/thunder3_stereo.wav", 44100, AL_FORMAT_STEREO16);
}

ThunderLight::~ThunderLight(void)
{
}

void ThunderLight::generateDirection(void)
{
	_light->setDirection(glm::normalize(glm::vec3(static_cast<GLfloat>(rand()) / RAND_MAX, -1.0f, static_cast<GLfloat>(rand()) / RAND_MAX)));
}

void ThunderLight::playRandomSound(void)
{
	_sound[rand() % 4]->play();
}

const std::shared_ptr<Graphics::DirLight> &ThunderLight::getLight(void) const
{
	return _light;
}