#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/matrix_access.hpp>
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
	}

	void BindAttribute(int attributeIndex, std::string attributeName)
	{
		const GLchar* attrName = attributeName.c_str();
		glBindAttribLocation(programId, attributeIndex, attrName);
	}

	void Prepare()
	{
		glLinkProgram(programId);
		glValidateProgram(programId);
		prepared = true;
		CheckLinking();
		GetAllUniformLocations();
	}

	void Activate()
	{
		if (!this->prepared)
			std::cout << "Prepare method not called!!!" << std::endl;
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

	void GetAllUniformLocations()
	{
		location_transformMatrix = GetUniformLocation("transformationMatrix");
	}

	void LoadTRSToBuffer(glm::mat4 matrix)
	{
		LoadToUniformBuffer(location_transformMatrix, matrix);
	}
	
private:
	bool prepared = false;
	int programId;
	int vertexShaderId;
	int fragmentShaderId;

	int location_transformMatrix;

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

	int GetUniformLocation(std::string uniformName)
	{
		return glGetUniformLocation(programId, uniformName.c_str());
	}

	void LoadToUniformBuffer(int location, float value)
	{
		glUniform1f(location, value);
	}

	void LoadToUniformBuffer(int location, glm::vec3 value)
	{
		glUniform3f(location, value.x, value.y, value.z);
	}

	void LoadToUniformBuffer(int location, bool value)
	{
		glUniform1i(location, value);
	}

	void LoadToUniformBuffer(int location, glm::mat4& value) //& passing value by reference
	{
		//count:how many matrices that you provide
		glUniformMatrix4fv(location, 1, false, &value[0][0]); //get pointer of the referenced value
	}
};