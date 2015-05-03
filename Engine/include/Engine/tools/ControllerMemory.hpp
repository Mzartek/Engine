#ifndef CONTROLLERMEMORY_HEADER
#define CONTROLLERMEMORY_HEADER

#include "../Object.hpp"

namespace Engine
{
	enum ptr_t {OBJECT_PTR, TAB_OBJECT_PTR};
	struct mem_info
	{
		unsigned int ptr_count;
		ptr_t ptr_type;
		std::string location_string;
	};

	extern DLLAPI std::map<void *, mem_info> memory_map;
	
	extern DLLAPI void memory_state(void);

	template<typename T>
	T *_new_ptr(T *ptr, std::string location_string) {
		void *p = reinterpret_cast<void *>(ptr);

		if (memory_map.find(p) != memory_map.end())
		{
			std::cerr << "This is not a new ptr: " << location_string << std::endl;
			abort();
		}

		memory_map[p].ptr_count = 1;
		memory_map[p].ptr_type = OBJECT_PTR;
		memory_map[p].location_string = location_string;

		return ptr;
	}

	template<typename T>
	T *_new_ptr_tab(T *ptr, std::string location_string) {
		void *p = reinterpret_cast<void *>(ptr);

		if (memory_map.find(p) != memory_map.end())
		{
			std::cerr << "This is not a new ptr: " << location_string << std::endl;
			abort();
		}

		memory_map[p].ptr_count = 1;
		memory_map[p].ptr_type = TAB_OBJECT_PTR;
		memory_map[p].location_string = location_string;

		return ptr;
	}

	template<typename T>
	T *_copy_ptr(T *ptr, std::string location_string) {
		void *p = reinterpret_cast<void *>(ptr);
		std::map<void *, mem_info>::iterator it = memory_map.find(p);

		if (it == memory_map.end())
		{
			std::cerr << "Wrong ptr: " << location_string << std::endl;
			abort();
		}

		it->second.ptr_count++;

		return ptr;
	}

	template<typename T>
	void _release_ptr(T *ptr, std::string location_string) {
		void *p = reinterpret_cast<void *>(ptr);
		std::map<void *, mem_info>::iterator it = memory_map.find(p);

		if (it == memory_map.end())
		{
			std::cerr << "Wrong ptr: " << location_string << std::endl;
			abort();
		}

		it->second.ptr_count--;

		if (it->second.ptr_count == 0)
		{
			if (it->second.ptr_type == OBJECT_PTR)
				delete ptr;
			else
				delete[] ptr;

			memory_map.erase(it);
		}
	}
}

#define STRING_LOCATION std::string(__FILE__ + std::string(" ") + std::to_string(__LINE__))

#define new_ptr(ARG) Engine::_new_ptr(new ARG, STRING_LOCATION)
#define new_ptr_tab(ARG, TAB) Engine::_new_ptr_tab(new ARG[TAB], STRING_LOCATION)
#define copy_ptr(ARG) Engine::_copy_ptr(ARG, STRING_LOCATION)
#define release_ptr(ARG) Engine::_release_ptr(ARG, STRING_LOCATION)

#endif