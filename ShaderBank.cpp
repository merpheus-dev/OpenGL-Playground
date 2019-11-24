#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
class ShaderBank
{
public:
	ShaderBank(std::string vertexFile, std::string fragmentFile)
	{
		vertexShaderId = LoadShader(vertexFile, GL_VERTEX_SHADER);
		fragmentShaderId = LoadShader(fragmentFile, GL_FRAGMENT_SHADER);
		programId = glCreateProgram();
		glAttachShader(programId, vertexShaderId);
		glAttachShader(programId, fragmentShaderId);
		glLinkProgram(programId);
		glValidateProgram(programId);
		CheckLinking();
	}

	void BindAttribute(int attributeIndex, std::string attributeName)
	{
		const GLchar* attrName = attributeName.c_str();
		glBindAttribLocation(programId, attributeIndex, attrName);
	}

	void Activate()
	{
		glUseProgram(programId);
	}

	void Deactivate()
	{
		glUseProgram(0);
	}

	void Dispose()
	{
		Deactivate();
		glDetachShader(programId, vertexShaderId);
		glDetachShader(programId, fragmentShaderId);
		glDeleteShader(vertexShaderId);
		glDeleteShader(fragmentShaderId);
		glDeleteProgram(programId);
	}

private:
	int programId;
	int vertexShaderId;
	int fragmentShaderId;
	static int LoadShader(std::string shaderFileName, int shaderType)
	{
		auto sourceString = ReadShader(shaderFileName);
		const GLchar* source = sourceString.c_str();
		const int source_length = sourceString.size();

		int shader_id = glCreateShader(shaderType);
		glShaderSource(shader_id, 1, &source, &source_length);
		glCompileShader(shader_id);
		int result;
		glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
		if (result != GL_TRUE)
		{
			int log_length = 0;
			char message[2048];
			glGetShaderInfoLog(shader_id, 2048, &log_length, message);
			std::cout << message << std::endl;
		}
		return shader_id;
	}
	static std::string ReadShader(std::string shaderFileName)
	{
		std::ifstream inFile;
		inFile.open("Engine/Shaders/" + shaderFileName);
		if (!inFile)
			std::cout << "ERROR READING" + shaderFileName << std::endl;
		std::stringstream strStream;
		strStream << inFile.rdbuf();
		return  strStream.str();
	}

	void CheckLinking()
	{
		GLint program_linked;
		glGetProgramiv(programId, GL_LINK_STATUS, &program_linked);
		if (program_linked != GL_TRUE)
		{
			GLsizei log_length = 0;
			GLchar message[1024];
			glGetProgramInfoLog(programId, 1024, &log_length, message);
			std::cout << message << std::endl;
		}
	}
};