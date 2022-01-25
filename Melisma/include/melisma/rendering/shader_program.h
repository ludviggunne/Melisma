#pragma once
#include "melisma/core.h"

#include <map>

#include "glm/glm.hpp"
#include "glm/ext.hpp"

namespace melisma {
	
	class melismaAPI ShaderProgram {
	public:
		ShaderProgram();
		~ShaderProgram();

		bool Create(const char *vertex_path, const char *fragment_path);
		void Use() const;


		template<typename T>
		void SetUniform(int location, const T &value) const;

		template<typename T>
		void SetUniformArray(int location, unsigned int size, const T *arr) const;


		void SetUniform_Int(int location, const int		  &value) const;
		void SetUniform_Float(int location, const float	  &value) const;

		void SetUniform_Vec2(int location, const glm::vec2 &value) const;
		void SetUniform_Vec3(int location, const glm::vec3 &value) const;
		void SetUniform_Vec4(int location, const glm::vec4 &value) const;

		void SetUniform_Mat4(int location, const glm::mat4 &value) const;
		
		void SetUniform_IntArray(int location, unsigned int size, const int   *data) const;
		void SetUniform_FloatArray(int location, unsigned int size, const float *data) const;


		int GetUniformLocation(const char *name);

	private:
		unsigned int m_RendererID;
		std::map<const char *, int> m_LocationCache;
	};




	template<>
	inline void ShaderProgram::SetUniform<int>(int location, const int &value) const
	{
		SetUniform_Int(location, value);
	}

	template<>
	inline void ShaderProgram::SetUniform<float>(int location, const float &value) const
	{
		SetUniform_Float(location, value);
	}



	template<>
	inline void ShaderProgram::SetUniform<glm::vec2>(int location, const glm::vec2 &value) const
	{
		SetUniform_Vec2(location, value);
	}

	template<>
	inline void ShaderProgram::SetUniform<glm::vec3>(int location, const glm::vec3 &value) const
	{
		SetUniform_Vec3(location, value);
	}

	template<>
	inline void ShaderProgram::SetUniform<glm::vec4>(int location, const glm::vec4 &value) const
	{
		SetUniform_Vec4(location, value);
	}



	template<>
	inline void ShaderProgram::SetUniform<glm::mat4>(int location, const glm::mat4 &value) const
	{
		SetUniform_Mat4(location, value);
	}



	template<>
	inline void ShaderProgram::SetUniformArray<int>(int location, unsigned int size, const int *arr) const
	{
		SetUniform_IntArray(location, size, arr);
	}

	template<>
	inline void ShaderProgram::SetUniformArray<float>(int location, unsigned int size, const float *arr) const
	{
		SetUniform_FloatArray(location, size, arr);
	}




	// DEFAULT
	template<typename T>
	inline void ShaderProgram::SetUniform(int location, const T &value) const
	{
		mlLog("Type not supported by ShaderProgram::SetUniform");
		mlAssert(0);
	}
	template<typename T>
	inline void ShaderProgram::SetUniformArray(int location, unsigned int size, const T *arr) const
	{
		mlLog("Type not supported by ShaderProgram::SetUniformArray");
		mlAssert(0);
	}
}