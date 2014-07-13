#ifndef TEXT_ARRAY
#define TEXT_ARRAY

#include "GLHead.hpp"
#include "ShaderProgram.hpp"
#include "Window.hpp"

namespace engine
{
	class DLLAPI TextArray
	{
	private:
		GLuint _idTexture;
		GLuint _idVAO;
		GLuint _idVBO;
		ShaderProgram *_program;
		GLint _MVPLocation;
		GLint _textureLocation;
		GLfloat _mat[16];
		TTF_Font *_font;
		SDL_Color _color;
	public:
		TextArray(void);
		~TextArray(void);
		void config(const std::string font, GLuint size,
			    GLubyte r, GLubyte g, GLubyte b,
			    GLuint x, GLuint y, GLuint w, GLuint h, ShaderProgram *program, Window *window);
		void write(const std::string text);
		void display(void);
	};
}

#endif
