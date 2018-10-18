#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "stb_image.h"


#include <fstream>
#include <string>

class VertexArray;

class ShaderProgram
{
private:
	GLuint id;
	std::string vertShader;
	std::string fragShader;

public:
	ShaderProgram();
	ShaderProgram(std::string vert, std::string frag);
	
	void draw(VertexArray *vertexArray);
	
	void setUniform(std::string uniform, glm::vec4 value);
	void setUniform(std::string uniform, float value);
	void setUniform(std::string uniform, glm::mat4);
	void setUniform(std::string uniform, int);
	
	GLuint getId();

};