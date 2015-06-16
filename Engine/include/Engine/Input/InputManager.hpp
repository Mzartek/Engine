#ifndef INPUT_HEADER
#define INPUT_HEADER

#include "../Object.hpp"

namespace Engine
{
		namespace Input
		{
				class DLLAPI InputManager
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
						static InputManager &Instance(void);

				private:
						InputManager(void);
						~InputManager(void);

				public:
						GLboolean getKeyBoardState(GLubyte button) const;
						GLboolean getMouseState(GLubyte button) const;
						GLint getMouseRelX(void) const;
						GLint getMouseRelY(void) const;
						void refresh(void);
				};
		}
}

#endif