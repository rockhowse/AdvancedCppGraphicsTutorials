#include "GLSLProgram.h"
#include "Errors.h"

#include <fstream>
#include <vector>

GLSLProgram::GLSLProgram() : 
	_programID(0), 
	_vertexShaderID(0),
	_fragmentShaderID(0)
{

}


GLSLProgram::~GLSLProgram()
{
}

void GLSLProgram::compileShaders(const std::string& vertexShaderfilePath, std::string& fragmentShaderFilePath) {
	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

	if (!_vertexShaderID) {
		fatalError("Vertex shader failed to be created!");
	}

	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	if (!_fragmentShaderID) {
		fatalError("Fragment shader failed to be created!");
	}

	compileShader(vertexShaderfilePath, _vertexShaderID);
	compileShader(fragmentShaderFilePath, _fragmentShaderID);
}

void GLSLProgram::linkShaders() {

}

void GLSLProgram::compileShader(const std::string filePath, GLuint id) {
	std::ifstream vertexFile(filePath);

	if (vertexFile.fail()) {
		fatalError("Failed to open: " + filePath);
	}

	std::string fileContents = "";
	std::string line;

	while (std::getline(vertexFile, line)) {
		fileContents += line + "\n";
	}

	vertexFile.close();

	const char* contentsPtr = fileContents.c_str();
	glShaderSource(id, 1, &contentsPtr, nullptr);
	glCompileShader(id);

	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		// The MaxLength includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		// Provide the infolog in whatever manor you deem best.
		// Exit with failure

		glDeleteShader(id); // don't leak the shader

		std::printf("%s\n",
			&(errorLog[0]));

		fatalError("Shader" + filePath + " failed to compile");
	}

}

