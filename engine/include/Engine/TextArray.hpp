#ifndef TEXT_ARRAY
#define TEXT_ARRAY

#include "ShaderProgram.hpp"
#include "Renderer.hpp"

namespace engine
{
	class DLLAPI TextArray : public Object
	{
	private:
		GLuint _idTexture;
		GLuint _idVAO;
		GLuint _idVBO;
		glm::mat4 *_mat;
		ShaderProgram *_program;
		GLint _MVPLocation;
		GLint _textureLocation;
		TTF_Font *_font;
		SDL_Color _color;
	public:
		TextArray(void);
		~TextArray(void);
		void config(const GLchar *font, const GLuint &size,
			const GLubyte &r, const GLubyte &g, const GLubyte &b,
			const GLuint &x, const GLuint &y, const GLuint &w, const GLuint &h, ShaderProgram *program, Renderer *renderer);
		void write(const GLchar *text);
		void display(void);
	};
}

#endif
