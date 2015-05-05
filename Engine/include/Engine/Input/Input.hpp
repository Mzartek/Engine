#ifndef INPUT_HEADER
#define INPUT_HEADER

#include "../Object.hpp"

namespace Engine
{
	class DLLAPI Input : public Object
	{
	private:
		const GLubyte *_keyState;
		struct MOUSESTATE
		{
			GLint x;
			GLint y;
			GLuint buttons;
		} _mouseState;
	public:
		Input(void);
		~Input(void);
		GLboolean getKeyBoardState(const GLubyte &button) const;
		GLboolean getMouseState(const GLubyte &button) const;
		GLint getMouseRelX(void) const;
		GLint getMouseRelY(void) const;
		void refresh(void);
	};
}

#endif