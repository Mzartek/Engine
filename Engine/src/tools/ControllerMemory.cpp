#include <Engine/Tools/ControllerMemory.hpp>

std::map<void *, Engine::mem_info> Engine::memory_map;

void Engine::memory_state(void)
{
	for (std::map<void *, Engine::mem_info>::iterator it = memory_map.begin(); it != memory_map.end(); it++)
		std::cout << it->second.ptr_count << " " << it->second.location_string << std::endl;
}