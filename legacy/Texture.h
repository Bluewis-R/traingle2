#include <GL/glew.h>
#include <glm/glm.hpp>

#include "stb_image.h"
#include <string>

class Texture
{
	GLuint id;
	glm::vec2 size;

public:
	Texture(std::string path);
	glm::vec2 getSize();
	GLuint getId();

};
