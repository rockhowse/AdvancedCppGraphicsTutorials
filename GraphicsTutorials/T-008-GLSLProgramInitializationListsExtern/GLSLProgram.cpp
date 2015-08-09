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

	std::ifstream vertexFile(vertexShaderfilePath);

	if (vertexFile.fail()) {
		fatalError("Failed to open: " + vertexShaderfilePath);
	}

	std::string fileContents = "";
	std::string line;

	while (std::getline(vertexFile, line)) {
		fileContents += line + "\n";
	}

	vertexFile.close();

	const char* contentsPtr = fileContents.c_str();
	glShaderSource(_vertexShaderID, 1, &contentsPtr, nullptr);
	glCompileShader(_vertexShaderID);

	GLint success = 0;
	glGetShaderiv(_vertexShaderID, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(_vertexShaderID, GL_INFO_LOG_LENGTH, &maxLength);

		// The MaxLength includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(_vertexShaderID, maxLength, &maxLength, &errorLog[0]);

		// Provide the infolog in whatever manor you deem best.
		// Exit with failure

		glDeleteShader(_vertexShaderID); // don't leak the shader
		
		std::printf("%s\n",
			&(errorLog[0]));

		fatalError("Vertex shader failed to compile");
	}


}

void GLSLProgram::linkShaders() {

}
