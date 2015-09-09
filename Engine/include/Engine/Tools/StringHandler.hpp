#ifndef STRINGHANDLER_HEADER
#define STRINGHANDLER_HEADER

#include "../Object.hpp"

namespace Engine
{
	namespace Tools
	{
		extern DLLAPI std::string getDir(const char *filePath);
		extern DLLAPI char *readText(const char *filePath);
	}
}

#endif
