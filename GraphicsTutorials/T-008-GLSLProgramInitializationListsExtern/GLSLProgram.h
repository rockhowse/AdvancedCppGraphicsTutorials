#pragma once
#include <string>
#include <GL/glew.h>

class GLSLProgram
{
public:
	GLSLProgram();
	~GLSLProgram();

	void compileShaders(const std::string& vertexShaderfilePath, const std::string& fragmentShaderFilePath);

	void linkShaders();

	void addAttribute(const std::string& attributeName);

	void use();
	void unuse();

private:
	void GLSLProgram::compileShader(const std::string filePath, GLuint id);

	GLuint _numAttributes;
	GLuint _programID;

	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;
};

