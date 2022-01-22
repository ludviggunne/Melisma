#pragma once
#include "core.h"
//#include "core.h"

#define TYPE(type) #type

#if 0
#define mlLogRef(msg) mlLog("Ref<T>: " << msg)
#else
#define mlLogRef(msg)
#endif

namespace melisma {

	template<typename T>
	class Ref { // Melisma Warning: Not thread safe ?
	public:
		Ref() : m_Instance(nullptr), m_Refs(nullptr) {}

		template<typename... ArgT>
		static Ref Create(ArgT... args)
		{
			Ref ref; 

			ref.m_Instance = new T(args...);
			ref.m_Refs = new unsigned int;
			*(ref.m_Refs) = 1;

			mlLogRef("Created");

			return ref;
		}

		Ref(T *&&ptr) : Ref()
		{
			m_Instance = ptr;
			m_Refs     = new unsigned int;
			*m_Refs    = 1;
		}



		~Ref() 
		{
			if (m_Refs)
			{
				(*m_Refs)--;

				mlLogRef("Destructed, refs = " << *m_Refs);

				if (*m_Refs == 0) {
					delete m_Refs;
					delete m_Instance;

					mlLogRef("No references left, deleting data.");
				}
			}
		}



		Ref(const Ref &ref) : Ref()
		{
			m_Instance = ref.m_Instance;
			m_Refs     = ref.m_Refs;

			(*m_Refs)++;
			mlLogRef("lvalue copy, refs = " << *m_Refs);
		}

		Ref(Ref &&ref) noexcept : Ref()
		{
			m_Instance = ref.m_Instance;
			m_Refs     = ref.m_Refs;

			(*m_Refs)++;
			mlLogRef("rvalue copy, refs = " << *m_Refs);
		}

		Ref &operator=(const Ref &ref)
		{
			if (*this != ref) {
				m_Instance = ref.m_Instance;
				m_Refs     = ref.m_Refs;

				(*m_Refs)++;
				mlLogRef("lvalue assign, refs = " << *m_Refs);
			}

			return *this;
		}

		Ref &operator=(Ref &&ref) {
			if (*this != ref) {
				if (m_Instance)
				{
					(*m_Refs)--;
					mlLogRef("Reassigned, refs = " << *m_Refs);

					if (*m_Refs == 0) {
						delete m_Refs;
						delete m_Instance;

						mlLogRef("No references left, deleting data.");
					}
				}

				m_Instance = ref.m_Instance;
				m_Refs     = ref.m_Refs;

				(*m_Refs)++;
				mlLogRef("rvalue assign, refs = " << *m_Refs);
			}

			return *this;
		}

		T *operator->() const {
			return m_Instance;
		}

		bool operator==(const Ref &ref) {
			return m_Instance == ref.m_Instance;
		}

		bool operator!=(const Ref &ref) {
			return m_Instance != ref.m_Instance;
		}

	private:
		T *m_Instance;
		unsigned int *m_Refs;
	};
}