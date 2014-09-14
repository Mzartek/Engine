#ifndef OBJECT
#define OBJECT

#include "EngineHead.hpp"

namespace engine
{;
	class DLLAPI Object
	{
	private:
		static GLint _memState;
	public:
		Object(void);
		virtual ~Object(void);
		void *operator new(size_t sz);
		void *operator new[](size_t sz);
		void operator delete(void *p);
		void operator delete[](void *p);
		static GLint getMemoryState(void);
		static void saveMemoryInfo(const GLchar *filename);
	};
}

#endif
