#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
{
}

ShaderProgram::ShaderProgram(std::string vert, std::string frag)
{
}

void ShaderProgram::draw(VertexArray * vertexArray)
{
}

void ShaderProgram::SetUniform(std::string uniform, glm::vec4 value)
{
}

void ShaderProgram::SetUniform(std::string uniform, float value)
{
}

GLuint ShaderProgram::getId()
{
	return GLuint();
}
