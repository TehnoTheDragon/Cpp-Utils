#pragma once
#include <optional>
#include <map>
#include "utils/File.hpp"
#include "utils/math/Vector.hpp"
#include "utils/graphics/Color.hpp"
#include "OpenGL.hpp"

namespace OpenGL
{
	// ShaderVFG - Shader Vertex, Fragment, Geometry;
	struct ShaderVFG
	{
		std::optional<std::string> vertex;
		std::optional<std::string> fragment;
		std::optional<std::string> geometry;
	};

	// ShaderFilePaths - Can contain 3 paths to 3 different shader types.
	typedef ShaderVFG ShaderFilePaths;

	class Shader
	{
		RenderID ID;
		std::map<std::string, GLint> cachedUniforms;
	public:
		void Bind() const;
		void Unbind() const;

	public:
		Shader(const ShaderFilePaths& paths);
		Shader(const ShaderVFG& sources, bool);
		Shader(const Shader&) = delete;
		virtual ~Shader();

		GLint GetUniformLocation(const std::string& name);
	public:
		void SetInteger(const std::string& name, int value);
		void SetFloat(const std::string& name, float value);
		void SetBoolean(const std::string& name, bool value);

		void SetVector2f(const std::string& name, const math::Vector2f& value);
		void SetVector2i(const std::string& name, const math::Vector2i& value);

		void SetVector3f(const std::string& name, const math::Vector3f& value);
		void SetVector3i(const std::string& name, const math::Vector3i& value);

		void SetVector4f(const std::string& name, const math::Vector4f& value);
		void SetVector4i(const std::string& name, const math::Vector4i& value);

		void SetColor3(const std::string& name, const graphics::Color3& value);
	};

	static RenderID CompileShader(GLenum shaderType, const std::string& source);
}