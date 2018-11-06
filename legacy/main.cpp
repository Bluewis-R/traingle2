#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "stb_image.h"
#include <time.h>
#include <exception>

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"
#include "Texture.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int windowWidth = 800;
int windowHeight = 600;

int main(int argc, char *argv[])
{
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    throw std::exception();
  }

  SDL_Window *window = SDL_CreateWindow("Triangle",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

  if (!SDL_GL_CreateContext(window))
  {
	  throw std::exception();
  }

  if (glewInit() != GLEW_OK)
  {
	  throw std::exception();
  }

  // OPENGL code

  VertexArray *hallShape = new VertexArray("re_hall_baked.obj");
  Texture *hallTexture = new Texture("re_hall_diffuse.png");
  VertexArray *shape = new VertexArray("curuthers.obj");
  Texture *texture = new Texture("curuthers_diffuse.png");
  ShaderProgram *shaderProgram = new ShaderProgram("simple.vert", "simple.frag");

  //old stuff
  /*
  VertexBuffer* positions = new VertexBuffer();
  positions->add(glm::vec3(0.0f, 0.5f, 0.0f));
  positions->add(glm::vec3(-0.5f, -0.5f, 0.0f));
  positions->add(glm::vec3(0.5f, -0.5f, 0.0f));
  
  VertexBuffer* texCoords = new VertexBuffer();
  texCoords->add(glm::vec2(0.5f, 0.0f));
  texCoords->add(glm::vec2(0.0f, 1.0f));
  texCoords->add(glm::vec2(1.0f, 1.0f));

  VertexArray *shape = new VertexArray();
  shape->SetBuffer("in_Position", positions);
  shape->SetBuffer("in_TexCoord", texCoords);
  */

  //ShaderProgram *shaderProgram = new ShaderProgram("../shaders/simple.vert", "../shaders/simple.frag");
  /*
  //	loading image
  int w = 0;
  int h = 0;
  int channels = 0;

  unsigned char *data = stbi_load("dice.png", &w, &h, &channels, 4);
  if (!data)
  {
	  throw std::exception();
  }

  GLuint textureId = 0;
  glGenTextures(1, &textureId);

  if (!textureId)
  {
	  throw std::exception();
  }
  glBindTexture(GL_TEXTURE_2D, textureId);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  free(data);
  glGenerateMipmap(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0);

  */

  float angle = 0;


  bool quit = false;
	//while loop
  while(!quit)
  {
    SDL_Event event = {0};

    while(SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        quit = true;
      }
    }

	SDL_GetWindowSize(window, &windowWidth, &windowHeight);
	glViewport(0, 0, windowWidth, windowHeight);
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	shaderProgram->setUniform("in_Projection", glm::perspective(glm::radians(45.0f),
		(float)windowWidth / (float)windowHeight, 0.1f, 100.f));

	// Create a "camera"
	glm::mat4 model(1.0f);
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0, 1, 0));
	shaderProgram->setUniform("in_View", glm::inverse(model));

	// Draw the mansion
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(2.0f, -2.0f, -16.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	shaderProgram->setUniform("in_Model", model);
	shaderProgram->setUniform("in_Texture", hallTexture);
	shaderProgram->draw(hallShape);

	// Draw the cat
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0, -2.1f, -20.0f));
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0, 1, 0));
	shaderProgram->setUniform("in_Model", model);
	shaderProgram->setUniform("in_Texture", texture);
	shaderProgram->draw(shape);
    /*
	//Shader things
	shaderProgram->SetUniform("in_Projection", glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f));

	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(0, 0, -2.5f));
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0, 1, 0));

	

	shaderProgram->SetUniform("in_Model", model);
	shaderProgram->SetUniform("in_Texture", 1);
	shaderProgram->draw(shape);
	*/


	angle += 1.0f;
    
	SDL_GL_SwapWindow(window);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}


// testing
/*
// persp
shaderProgram->SetUniform("in_Projection", glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f));

glm::mat4 model(1.0f);
model = glm::translate(model, glm::vec3(0, 0, -2.5f));
model = glm::rotate(model, glm::radians(angle), glm::vec3(0,1,0));

shaderProgram->SetUniform("in_Model", model);
shaderProgram->draw(shape);

angle += 0.1f;


//ortho
shaderProgram->SetUniform("in_Projection", glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT, 0.0f, 1.0f));

model = glm::mat4 (1.0f);
model = glm::translate(model, glm::vec3(0, WINDOW_HEIGHT - 100, 0));
model = glm::scale(model, glm::vec3(100, 100, 1));

shaderProgram->SetUniform("in_Model", model);
shaderProgram->draw(shape);

angle += 0.1f;

*/