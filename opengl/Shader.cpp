#include "Shader.hpp"

namespace OpenGL
{
	RenderID CompileShader(GLenum shaderType, const std::string& source)
	{
		RenderID shaderID = glCreateShader(shaderType);
		const char* csource = source.c_str();
		GLCall(glShaderSource(shaderID, 1, &csource, nullptr));
		GLCall(glCompileShader(shaderID));

		int r;
		GLCall(glGetShaderiv(shaderID, GL_COMPILE_STATUS, &r));
		if (r == GL_FALSE)
		{
			int l;
			GLCall(glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &l));
			char* message = (char*)_malloca(l * sizeof(char));
			GLCall(glGetShaderInfoLog(shaderID, l, &l, message));
			std::cout << "Failed to compile " <<
					( shaderType == GL_VERTEX_SHADER ? "VERTEX" 
					: shaderType == GL_FRAGMENT_SHADER ? "FRAGMENT" 
					: shaderType == GL_GEOMETRY_SHADER ? "GEOMTRY" 
					: "UNKNOWN"  ) << " shader!" << std::endl;
			std::cout << message << std::endl;

			GLCall(glDeleteShader(shaderID));

			return 0;
		}

		return shaderID;
	}

	Shader::Shader(const ShaderFilePaths& paths)
	{
		ShaderVFG vfg;
		vfg.vertex = util::File::ReadAndClose(paths.vertex.value_or(""));
		vfg.fragment = util::File::ReadAndClose(paths.fragment.value_or(""));
		//vfg.geometry = util::File::ReadAndClose(paths.geometry.value_or(""));

		GLCall(ID = glCreateProgram());

		RenderID VS = CompileShader(GL_VERTEX_SHADER, vfg.vertex.value_or("void main() {}"));
		RenderID FS = CompileShader(GL_FRAGMENT_SHADER, vfg.fragment.value_or("void main() {}"));
		//RenderID GS = CompileShader(GL_GEOMETRY_SHADER, vfg.geometry.value_or("void main() {}"));

		if (VS > 0) GLCall(glAttachShader(ID, VS));
		if (FS > 0) GLCall(glAttachShader(ID, FS));
		//if (GS > 0) GLCall(glAttachShader(ID, GS));

		GLCall(glLinkProgram(ID));
		GLCall(glValidateProgram(ID));

		if (VS > 0) GLCall(glDeleteShader(VS));
		if (FS > 0) GLCall(glDeleteShader(FS));
		//if (GS > 0) GLCall(glDeleteShader(GS));
	}

	Shader::Shader(const ShaderVFG& sources, bool)
	{
		GLCall(ID = glCreateProgram());

		RenderID VS = CompileShader(GL_VERTEX_SHADER, sources.vertex.value_or("void main() {}"));
		RenderID FS = CompileShader(GL_FRAGMENT_SHADER, sources.fragment.value_or("void main() {}"));
		//RenderID GS = CompileShader(GL_GEOMETRY_SHADER, sources.geometry.value_or("void main() {}"));

		if (VS > 0) GLCall(glAttachShader(ID, VS));
		if (FS > 0) GLCall(glAttachShader(ID, FS));
		//if (GS > 0) GLCall(glAttachShader(ID, GS));

		GLCall(glLinkProgram(ID));
		GLCall(glValidateProgram(ID));

		if (VS > 0) GLCall(glDeleteShader(VS));
		if (FS > 0) GLCall(glDeleteShader(FS));
		//if (GS > 0) GLCall(glDeleteShader(GS));
	}

	Shader::~Shader()
	{
		GLCall(glDeleteProgram(ID));
	}

	void Shader::Bind() const
	{
		GLCall(glUseProgram(ID));
	}

	void Shader::Unbind() const
	{
		GLCall(glUseProgram(0));
	}

	GLint Shader::GetUniformLocation(const std::string& name)
	{
		if (cachedUniforms.find(name) != cachedUniforms.end())
			return cachedUniforms[name];

		GLCall(GLint location = glGetUniformLocation(ID, name.c_str()));
		cachedUniforms[name] = location;

		return location;
	}

	void Shader::SetInteger(const std::string& name, int value)
	{
		GLCall(glUniform1i(GetUniformLocation(name), value));
	}
	void Shader::SetFloat(const std::string& name, float value)
	{
		GLCall(glUniform1f(GetUniformLocation(name), value));
	}
	void Shader::SetBoolean(const std::string& name, bool value)
	{
		GLCall(glUniform1i(GetUniformLocation(name), value ? 1 : 0));
	}

	void Shader::SetVector2f(const std::string& name, const math::Vector2f& value)
	{
		GLCall(glUniform2f(GetUniformLocation(name), value.x, value.y));
	}
	void Shader::SetVector2i(const std::string& name, const math::Vector2i& value)
	{
		GLCall(glUniform2i(GetUniformLocation(name), value.x, value.y));
	}

	void Shader::SetVector3f(const std::string& name, const math::Vector3f& value)
	{
		GLCall(glUniform3f(GetUniformLocation(name), value.x, value.y, value.z));
	}
	void Shader::SetVector3i(const std::string& name, const math::Vector3i& value)
	{
		GLCall(glUniform3i(GetUniformLocation(name), value.x, value.y, value.z));
	}

	void Shader::SetVector4f(const std::string& name, const math::Vector4f& value)
	{
		GLCall(glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w));
	}
	void Shader::SetVector4i(const std::string& name, const math::Vector4i& value)
	{
		GLCall(glUniform4i(GetUniformLocation(name), value.x, value.y, value.z, value.w));
	}

	void Shader::SetColor3(const std::string& name, const graphics::Color3& value)
	{
		GLCall(glUniform3f(GetUniformLocation(name), (float)value.R / 255.f, (float)value.G / 255.f, (float)value.B / 255.f));
	}

}