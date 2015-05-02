#ifndef CONTROLLERMEMORY_HEADER
#define CONTROLLERMEMORY_HEADER

#include <Engine/Object.hpp>

namespace Engine
{
	enum ref_t {REF_PTR, REF_TAB_PTR};
	struct mem_info
	{
		unsigned int ref_count;
		ref_t ref_type;
		std::string location_string;
	};

	extern DLLAPI std::map<void *, mem_info> memory_map;
	
	extern DLLAPI void memory_state(void);

	template<typename T>
	T *_new_ref(T *ref, std::string location_string) {
		void *p = reinterpret_cast<void *>(ref);

		if (memory_map.find(p) != memory_map.end())
		{
			std::cerr << "This is not a new ref: " << location_string << std::endl;
			abort();
		}

		memory_map[p].ref_count = 1;
		memory_map[p].ref_type = REF_PTR;
		memory_map[p].location_string = location_string;

		return ref;
	}

	template<typename T>
	T *_new_ref_tab(T *ref, std::string location_string) {
		void *p = reinterpret_cast<void *>(ref);

		if (memory_map.find(p) != memory_map.end())
		{
			std::cerr << "This is not a new ref: " << location_string << std::endl;
			abort();
		}

		memory_map[p].ref_count = 1;
		memory_map[p].ref_type = REF_TAB_PTR;
		memory_map[p].location_string = location_string;

		return ref;
	}

	template<typename T>
	T *_copy_ref(T *ref, std::string location_string) {
		void *p = reinterpret_cast<void *>(ref);
		std::map<void *, mem_info>::iterator it = memory_map.find(p);

		if (it == memory_map.end())
		{
			std::cerr << "Wrong ref: " << location_string << std::endl;
			abort();
		}

		it->second.ref_count++;

		return ref;
	}

	template<typename T>
	void _release_ref(T *ref, std::string location_string) {
		void *p = reinterpret_cast<void *>(ref);
		std::map<void *, mem_info>::iterator it = memory_map.find(p);

		if (it == memory_map.end())
		{
			std::cerr << "Wrong ref: " << location_string << std::endl;
			abort();
		}

		it->second.ref_count--;

		if (it->second.ref_count == 0)
		{
			if (it->second.ref_type == REF_PTR)
				delete ref;
			else
				delete[] ref;

			memory_map.erase(it);
		}
	}
}

#define STRING_LOCATION std::string(__FILE__ + std::string(" ") + std::to_string(__LINE__))

#define new_ref(ARG) Engine::_new_ref(new ARG, STRING_LOCATION)
#define new_ref_tab(ARG, TAB) Engine::_new_ref_tab(new ARG[TAB], STRING_LOCATION)
#define copy_ref(ARG) Engine::_copy_ref(ARG, STRING_LOCATION)
#define release_ref(ARG) Engine::_release_ref(ARG, STRING_LOCATION)

#endif