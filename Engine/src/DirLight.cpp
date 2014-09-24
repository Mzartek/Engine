#include <Engine/DirLight.hpp>
#include <Engine/Buffer.hpp>
#include <Engine/ShadowMap.hpp>
#include <Engine/ShaderProgram.hpp>
#include <Engine/GBuffer.hpp>
#include <Engine/Camera.hpp>

engine::DirLight::DirLight(void)
{
}

engine::DirLight::~DirLight(void)
{
}

#define BUFFER_OFFSET(i) ((GLbyte *)NULL + i)

void engine::DirLight::config(ShaderProgram *program)
{
	_program = program;

	// Layout
	GLfloat vertex[] = {
		-1, -1,
		1, -1,
		-1, 1,
		1, 1,
	};
	_vertexBuffer->createStore(GL_ARRAY_BUFFER, vertex, sizeof vertex, GL_STATIC_DRAW);
	_shadowMatrixBuffer->createStore(GL_UNIFORM_BUFFER, NULL, sizeof(glm::mat4), GL_DYNAMIC_DRAW);
	_IVPMatrixBuffer->createStore(GL_UNIFORM_BUFFER, NULL, sizeof(glm::mat4), GL_DYNAMIC_DRAW);
	_screenBuffer->createStore(GL_UNIFORM_BUFFER, NULL, 16, GL_DYNAMIC_DRAW);
	_cameraBuffer->createStore(GL_UNIFORM_BUFFER, NULL, 16, GL_DYNAMIC_DRAW);
	_lightInfoBuffer->createStore(GL_UNIFORM_BUFFER, NULL, sizeof _lightInfo, GL_DYNAMIC_DRAW);

	glBindVertexArray(_idVAO);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer->getId());
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), BUFFER_OFFSET(0));
	glBindVertexArray(0);

	glUseProgram(_program->getId());	
	glUniform1i(glGetUniformLocation(_program->getId(), "normalTexture"), 0);
	glUniform1i(glGetUniformLocation(_program->getId(), "materialTexture"), 1);
	glUniform1i(glGetUniformLocation(_program->getId(), "depthTexture"), 2);
	glUniform1i(glGetUniformLocation(_program->getId(), "shadowMap"), 3);
	glUseProgram(0);
}

#undef BUFFER_OFFSET

void engine::DirLight::setColor(const glm::vec3 &color)
{
	_lightInfo.color = color;
}

void engine::DirLight::setDirection(const glm::vec3 &dir)
{
	_lightInfo.direction = dir;
}

void engine::DirLight::setShadowMapping(const GLboolean &shadow)
{
	_lightInfo.withShadowMapping = shadow;
}

glm::vec3 engine::DirLight::getColor(void) const
{
	return _lightInfo.color;
}

glm::vec3 engine::DirLight::getDirection(void) const
{
	return _lightInfo.direction;
}

void engine::DirLight::position(const glm::vec3 &position, const GLfloat &dim)
{
	*_VPMatrix = glm::ortho(-dim, dim, -dim, dim, -dim, dim)
		* glm::lookAt(position - _lightInfo.direction, position, glm::vec3(0.0f, 1.0f, 0.0f));
}

void engine::DirLight::display(GBuffer *gbuf, Camera *cam)
{
	gbuf->setLightState();

	glUseProgram(_program->getId());

	// GBuffer
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gbuf->getIdTexture(GBUF_NORMAL));

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, gbuf->getIdTexture(GBUF_MATERIAL));

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, gbuf->getIdTexture(GBUF_DEPTH_STENCIL));

	// ShadowMap
	if (_lightInfo.withShadowMapping == GL_TRUE)
	{
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, _shadow->getIdDepthTexture());

		_shadowMatrixBuffer->updateStoreMap(_VPMatrix);
		glBindBufferBase(GL_UNIFORM_BUFFER, 0, _shadowMatrixBuffer->getId());
	}

	_IVPMatrixBuffer->updateStoreMap(glm::value_ptr(glm::inverse(cam->getVPMatrix())));
	_screenBuffer->updateStoreMap(glm::value_ptr(glm::uvec2(gbuf->getWidth(), gbuf->getHeight())));
	_cameraBuffer->updateStoreMap(glm::value_ptr(glm::vec3(cam->getPositionCamera().x, cam->getPositionCamera().y, cam->getPositionCamera().z)));
	_lightInfoBuffer->updateStoreMap(&_lightInfo);

	glBindBufferBase(GL_UNIFORM_BUFFER, 1, _IVPMatrixBuffer->getId());
	glBindBufferBase(GL_UNIFORM_BUFFER, 2, _screenBuffer->getId());
	glBindBufferBase(GL_UNIFORM_BUFFER, 3, _cameraBuffer->getId());
	glBindBufferBase(GL_UNIFORM_BUFFER, 4, _lightInfoBuffer->getId());

	glBindVertexArray(_idVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);

	glUseProgram(0);

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}
