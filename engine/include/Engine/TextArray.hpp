#ifndef TEXT_ARRAY
#define TEXT_ARRAY

#include "Object.hpp"

namespace engine
{
	class ShaderProgram;
	class Renderer;

	class DLLAPI TextArray : public Object
	{
	private:
		GLuint _idTexture;
		GLuint _idVAO;
		GLuint _idVBO;
		TTF_Font *_font;
		glm::mat4 *_mat;
		// Do not delete it
		ShaderProgram *_program;
		// Location or Index
		GLint _MVPLocation;
		GLint _textureLocation;
		// SDL Feature
		SDL_Color _color;
	public:
		TextArray(void);
		~TextArray(void);
		void config(const GLchar *font, const GLuint &size,
			const GLubyte &r, const GLubyte &g, const GLubyte &b,
			const GLuint &x, const GLuint &y, const GLuint &w, const GLuint &h, ShaderProgram *program, Renderer *renderer);
		void write(const GLchar *text);
		void display(Renderer *renderer);
	};
}

#endif
