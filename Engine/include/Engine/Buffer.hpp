#ifndef BUFFER
#define BUFFER

#include "Object.hpp"

namespace engine
{
	class DLLAPI Buffer : public Object
	{
	private:
		GLenum _target;
		GLuint _idBuffer;
		GLsizeiptr _size;
	public:
		Buffer(void);
		~Buffer(void);
		GLenum getTarget(void);
		GLuint getId(void);
		void createStore(const GLenum &target, const GLvoid *data, const GLsizeiptr &size, const GLenum &usage);
		void updateStoreSub(const GLvoid *data);
		void updateStoreMap(const GLvoid *data);
	};
}

#endif