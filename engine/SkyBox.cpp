#include <Engine/SkyBox.hpp>

engine::SkyBox::SkyBox()
{
	_idTexture = 0;
	_idVAO = 0;
	_idVBO = 0;
	_idIBO = 0;
	_rotateMatrix = new glm::mat4;
	_program = NULL;
}

engine::SkyBox::~SkyBox()
{
	if(glIsTexture(_idTexture))
		glDeleteTextures(1, &_idTexture);
	if(glIsVertexArray(_idVAO))
		glDeleteVertexArrays(1, &_idVAO);
	if(glIsBuffer(_idVBO))
		glDeleteBuffers(1, &_idVBO);
	if(glIsBuffer(_idIBO))
		glDeleteBuffers(1, &_idIBO);
	delete _rotateMatrix;
}

#define BUFFER_OFFSET(i) ((GLbyte *)NULL + i)

void engine::SkyBox::load(const GLchar *posx, const GLchar *negx,
	const GLchar *posy, const GLchar *negy,
	const GLchar *posz, const GLchar *negz,
	GLfloat dim, ShaderProgram *program)
{
	GLuint i;
	GLenum cube_map_target[] = {
		GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
	};
	SDL_Surface *image[6];
	image[0] = IMG_Load(posx);
	image[1] = IMG_Load(negx);
	image[2] = IMG_Load(posy);
	image[3] = IMG_Load(negy);
	image[4] = IMG_Load(posz);
	image[5] = IMG_Load(negz);

	if(glIsTexture(_idTexture))
		glDeleteTextures(1, &_idTexture);
	glGenTextures(1, &_idTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _idTexture);

	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	for(i=0 ; i<6 ; i++)
	{
		if(image[i]==NULL)
		{
			std::cerr << "Error while loading image" << std::endl;
			exit(1);
		}
		switch(testFormat(image[i]->format->format))
		{
		case RGB:
			glTexImage2D(cube_map_target[i], 0, GL_RGB8, image[i]->w, image[i]->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image[i]->pixels);
			break;
		case BGR:
			glTexImage2D(cube_map_target[i], 0, GL_RGB8, image[i]->w, image[i]->h, 0, GL_BGR, GL_UNSIGNED_BYTE, image[i]->pixels);
			break;
		case RGBA:
			glTexImage2D(cube_map_target[i], 0, GL_RGBA8, image[i]->w, image[i]->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image[i]->pixels);
			break;
		default:
			std::cerr << "Format " << image[i]->format->format << " unknown" << std::endl;
			break;
		}
		SDL_FreeSurface(image[i]);
	}

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	GLfloat vertexArray[] = {
		+dim, -dim, -dim,
		-dim, -dim, -dim,
		-dim, -dim, +dim,
		+dim, -dim, +dim,
		+dim, +dim, -dim,
		-dim, +dim, -dim,
		-dim, +dim, +dim,
		+dim, +dim, +dim
	};
	GLuint indexArray[] = {
		0, 1, 2, 0, 2, 3,
		4, 7, 6, 4, 6, 5,
		0, 4, 5, 0, 5, 1,
		3, 2, 6, 3, 6, 7,
		1, 5, 6, 1, 6, 2,
		0, 3, 7, 0, 7, 4
	};
	_numElement = sizeof(indexArray) / sizeof(GLuint);

	if(glIsVertexArray(_idVAO))
		glDeleteVertexArrays(1, &_idVAO);
	glGenVertexArrays(1, &_idVAO);
	glBindVertexArray(_idVAO);

	if(glIsBuffer(_idVBO))
		glDeleteBuffers(1, &_idVBO);
	glGenBuffers(1, &_idVBO);
	glBindBuffer(GL_ARRAY_BUFFER, _idVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof vertexArray, vertexArray, GL_STATIC_DRAW);

	if(glIsBuffer(_idIBO))
		glDeleteBuffers(1, &_idIBO);
	glGenBuffers(1, &_idIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _idIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof indexArray, indexArray, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, GLsizei(3*sizeof(GLfloat)), BUFFER_OFFSET(0));

	glBindVertexArray(0);

	_program = program;
	_MVPLovation = glGetUniformLocation(_program->getId(), "MVP");
	_cubeMapLocation = glGetUniformLocation(_program->getId(), "cubeMap");
}

#undef BUFFER_OFFSET

void engine::SkyBox::rotate(const GLfloat &angle, const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
	*_rotateMatrix *= glm::rotate(angle * ((GLfloat)M_PI / 180), glm::vec3(x, y, z));
}

void engine::SkyBox::display(GBuffer *gbuf, Camera *cam) const
{
	glm::mat4 pos = glm::translate(glm::vec3(cam->getPositionCamera()));
	pos *= *_rotateMatrix;
	pos = cam->getVPMatrix() * pos;

	gbuf->setSkyboxConfig();

	glUseProgram(_program->getId());

	glUniformMatrix4fv(_MVPLovation, 1, GL_FALSE, glm::value_ptr(pos));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _idTexture);
	glUniform1i(_cubeMapLocation, 0);

	glBindVertexArray(_idVAO);
	glDrawElements(GL_TRIANGLES, _numElement, GL_UNSIGNED_INT, 0);	
	glBindVertexArray(0);

	glUseProgram(0);

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}
