#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <exception>

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

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

  VertexBuffer* positions = new VertexBuffer();
  positions->add(glm::vec3(0.0f, 0.5f, 0.0f));
  positions->add(glm::vec3(-0.5f, -0.5f, 0.0f));
  positions->add(glm::vec3(0.5f, -0.5f, 0.0f));

  VertexBuffer* colors = new VertexBuffer();
  positions->add(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
  positions->add(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
  positions->add(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

  VertexArray *shape = new VertexArray();
  shape->SetBuffer("in_Position", positions);
  shape->SetBuffer("in_Color", colors);

  ShaderProgram *shaderProgram = new ShaderProgram("../shader/simple.vert", "..shaders/simple.frag");



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


		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
    
    shaderProgram->draw(shape);
    
		SDL_GL_SwapWindow(window);
    }
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
