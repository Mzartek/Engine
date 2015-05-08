#ifndef INPUT_HEADER
#define INPUT_HEADER

#include "../Object.hpp"

namespace Engine
{
	class DLLAPI Input
	{
	private:
		Input(void);
		~Input(void);

		const GLubyte *_keyState;
		struct MOUSESTATE
		{
			GLint x;
			GLint y;
			GLuint buttons;
		} _mouseState;

	public:
		static Input &Instance(void);

		GLboolean getKeyBoardState(GLubyte button) const;
		GLboolean getMouseState(GLubyte button) const;
		GLint getMouseRelX(void) const;
		GLint getMouseRelY(void) const;
		void refresh(void);
	};
}

#endif