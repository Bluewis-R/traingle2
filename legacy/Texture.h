#ifndef _TEXTURE_H_
#define _TEXTURE_H_

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
#endif