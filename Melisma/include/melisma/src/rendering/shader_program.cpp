#include "rendering/shader_program.h"
#include "glcall.h"

#include "glad/glad.h"

#include <fstream>
#include <sstream>

namespace melisma {



	ShaderProgram::ShaderProgram() : m_RendererID(0)
	{
	}

	ShaderProgram::~ShaderProgram()
	{
		GLcall(glDeleteProgram(m_RendererID));
	}

	bool ShaderProgram::Create(const char *vertex_path, const char *fragment_path)
	{
		bool success = true;

		/* Read source files */
		std::ifstream vfile, ffile;

		vfile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		ffile.exceptions(std::ifstream::failbit | std::ifstream::badbit);


		try {
			vfile.open(vertex_path);
		}
		catch (std::ios_base::failure &e) {
			mlLog("Failed to open vertex shader source file: " << e.what());
			success = false;
		}
		try {
			ffile.open(fragment_path);
		}
		catch (std::ios_base::failure &e) {
			mlLog("Failed to open fragment shader source file: " << e.what());
			success = false;
		}

		if (!success) return false;

		std::stringstream vstream, fstream;

		vstream << vfile.rdbuf();
		fstream << ffile.rdbuf();

		vfile.close();
		ffile.close();

		std::string
			vstring = vstream.str(),
			fstring = fstream.str();

		const char
			*vsource = vstring.c_str(),
			*fsource = fstring.c_str();


		/* Compile shaders and check status */
		GLcall(unsigned int vshader = glCreateShader(GL_VERTEX_SHADER));
		GLcall(unsigned int fshader = glCreateShader(GL_FRAGMENT_SHADER));

		GLcall(glShaderSource(vshader, 1, &vsource, NULL));
		GLcall(glShaderSource(fshader, 1, &fsource, NULL));

		GLcall(glCompileShader(vshader));
		GLcall(glCompileShader(fshader));


		int status;
		char log[512];

		GLcall(glGetShaderiv(vshader, GL_COMPILE_STATUS, &status));
		if (!status) {
			GLcall(glGetShaderInfoLog(vshader, 512, 0, log));
			mlLog("Failed to compile vertex shader: " << log);
			success = false;
		}

		GLcall(glGetShaderiv(fshader, GL_COMPILE_STATUS, &status));
		if (!status) {
			GLcall(glGetShaderInfoLog(fshader, 512, 0, log));
			mlLog("Failed to compile fragment shader: " << log);
			success = false;
		}


		/* Link shaders and check status */
		GLcall(m_RendererID = glCreateProgram());

		GLcall(glAttachShader(m_RendererID, vshader));
		GLcall(glAttachShader(m_RendererID, fshader));

		GLcall(glLinkProgram(m_RendererID));


		GLcall(glGetProgramiv(m_RendererID, GL_LINK_STATUS, &status));
		if (!status) {
			GLcall(glGetProgramInfoLog(m_RendererID, 512, 0, log));
			mlLog("Failed to link shader program: " << log);
			success = false;
		}

		GLcall(glDeleteShader(vshader));
		GLcall(glDeleteShader(fshader));


		return success;
	}

	void ShaderProgram::Use() const
	{
		GLcall(glUseProgram(m_RendererID));
	}

	int ShaderProgram::GetUniformLocation(const char *name)
	{
		auto it = m_LocationCache.find(name);

		if (it != m_LocationCache.end())
			return it->second;

		int location = glGetUniformLocation(m_RendererID, name);
		if (location == -1)
			mlLog("Couldn't find location of uniform '" << name << "'");

		m_LocationCache[name] = location;
		
		return location;
	}

	void ShaderProgram::SetUniform_Int(int location, const int &value) const
	{
		Use();
		GLcall(glUniform1i(location, value));
	}

	void ShaderProgram::SetUniform_Float(int location, const float &value) const
	{
		Use();
		GLcall(glUniform1f(location, value));
	}

	void ShaderProgram::SetUniform_Vec2(int location, const glm::vec2 &value) const
	{
		Use();
		GLcall(glUniform1fv(location, 2, glm::value_ptr(value)));
	}

	void ShaderProgram::SetUniform_Vec3(int location, const glm::vec3 &value) const
	{
		Use();
		GLcall(glUniform1fv(location, 3, glm::value_ptr(value)));
	}

	void ShaderProgram::SetUniform_Vec4(int location, const glm::vec4 &value) const
	{
		Use();
		GLcall(glUniform1fv(location, 4, glm::value_ptr(value)));
	}

	void ShaderProgram::SetUniform_Mat4(int location, const glm::mat4 &value) const
	{
		Use();
		GLcall(glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value)));
	}

	void ShaderProgram::SetUniform_IntArray(int location, unsigned int size, const int *data) const
	{
		Use();
		GLcall(glUniform1iv(location, size, data));
	}

	void ShaderProgram::SetUniform_FloatArray(int location, unsigned int size, const float *data) const
	{
		Use();
		GLcall(glUniform1fv(location, size, data));
	}

}