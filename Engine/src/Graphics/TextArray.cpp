#include <Engine/Graphics/TextArray.hpp>

Engine::Graphics::TextArray::TextArray(const std::shared_ptr<ShaderProgram> &program)
	: _font(NULL), _program(program)
{
	_texture = std::shared_ptr<Texture2D>(new Texture2D);
	_vertexBuffer = std::shared_ptr<Buffer>(new Buffer);

	_vertexBuffer->createStore(GL_ARRAY_BUFFER, NULL, 64, GL_STATIC_DRAW);

	glUseProgram(_program->getId());
	glUniform1i(glGetUniformLocation(_program->getId(), "textTexture"), 0);

	glGenVertexArrays(1, &_idVAO);
	glBindVertexArray(_idVAO);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer->getId());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), BUFFER_OFFSET(0));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), BUFFER_OFFSET(2 * sizeof(GLfloat)));
	glBindVertexArray(0);
}

Engine::Graphics::TextArray::~TextArray(void)
{
	glDeleteVertexArrays(1, &_idVAO);
}

void Engine::Graphics::TextArray::setFont(const GLchar *font, GLuint size, GLubyte r, GLubyte g, GLubyte b)
{
	if (_font) TTF_CloseFont(_font);
	_font = TTF_OpenFont(font, size);
	if (_font == NULL)
	{
		std::cerr << "Error while loading fontFile: " << font << std::endl;
		exit(1);
	}

	_color.r = b;
	_color.g = g;
	_color.b = r;
	_color.a = 0;
}

void Engine::Graphics::TextArray::writeScreen(GLuint x, GLuint y, GLuint w, GLuint h, const GLchar *text)
{
	SDL_Surface *t;

	t = TTF_RenderText_Blended(_font, &text[0], _color);
	_texture->loadFromSDL_Surface(t);
	SDL_FreeSurface(t);

	GLfloat vertexArray[] =
	{
		(GLfloat)x, (GLfloat)y,
		0, 0,
		(GLfloat)x + w, (GLfloat)y,
		1, 0,
		(GLfloat)x, (GLfloat)y + h,
		0, 1,
		(GLfloat)x + w, (GLfloat)y + h,
		1, 1,
	};
	_vertexBuffer->updateStoreSub(vertexArray);
}

void Engine::Graphics::TextArray::writeScreen(const GLchar *text) const
{
	SDL_Surface *t;

	t = TTF_RenderText_Blended(_font, &text[0], _color);
	_texture->loadFromSDL_Surface(t);
	SDL_FreeSurface(t);
}

void Engine::Graphics::TextArray::display(const std::shared_ptr<CBuffer> &cbuf) const
{
	cbuf->setTransparentState();

	glUseProgram(_program->getId());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texture->getId());

	glBindVertexArray(_idVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}
