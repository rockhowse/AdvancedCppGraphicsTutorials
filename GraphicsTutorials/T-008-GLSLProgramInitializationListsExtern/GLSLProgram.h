#pragma once
#include <string>
#include <GL/glew.h>

class GLSLProgram
{
public:
	GLSLProgram();
	~GLSLProgram();

	void compileShaders(const std::string& vertexShaderfilePath, std::string& fragmentShaderFilePath);

	void linkShaders();

private:
	GLuint _programID;

	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;
};

