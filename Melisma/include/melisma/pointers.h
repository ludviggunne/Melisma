#pragma once
#include "core.h"
//#include "core.h"

#if 0
#define mlLogRef(msg) mlLog(msg)
#else
#define mlLogRef(msg)
#endif

namespace melisma {

	template<typename T>
	class Ref {
	public:
		template<typename... ArgT>
		Ref(ArgT... args) : m_Instance(nullptr), m_Refs(nullptr) 
		{
			m_Instance = new T(args...);
			m_Refs     = new unsigned int;
			*m_Refs    = 1;
		}

		Ref(T *&&ptr)
		{
			m_Instance = ptr;
			m_Refs = new unsigned int;
			*m_Refs = 1;
		}

		~Ref() 
		{
			*m_Refs--;

			if (*m_Refs == 0) {
				delete m_Refs;
				delete m_Instance;
			}
		}

		Ref(const Ref &ref) 
		{
			*this = ref;
		}

		Ref(Ref &&ref) = delete; // Melisma Todo: impl rvalue constructor ?

		Ref &operator=(const Ref &ref)
		{
			m_Instance = ref.m_Instance;
			m_Refs = ref.m_Refs;

			*m_Refs++;
		}

		Ref &operator=(Ref &&ref) = delete;

		T *operator->() const {
			return m_Instance;
		}

	private:
		T *m_Instance;
		unsigned int m_Refs;
	};

}