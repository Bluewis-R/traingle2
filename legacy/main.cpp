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

  bool quit = false;
  
  //CODE

  VertexBuffer* positions = new VertexBuffer();
  positions->add(glm::vec3(0.0f, 0.5f, 0.0f));
  positions->add(glm::vec3(-0.5f, -0.5f, 0.0f));
  positions->add(glm::vec3(0.5f, -0.5f, 0.0f));

  VertexBuffer* colors = new VertexBuffer();
  positions->add(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
  positions->add(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
  positions->add(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));


	glBindVertex(vaoId);
	// bind the position VBO, assighnhsvaujhdvsakjhvdujsahvd
	glBindBuffer(GL_ARRAY_BUFFER, positions->GetId());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
	glEnableVertexAttribArray(0);
	//comment goes here
	glBindBuffer(GL_ARRAY_BUFFER, colors->GetId());
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizof(GLfloat), (void *)0);
	glEnableVertexAttribArray(1);

	//another comment
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	Gluint vertexShaderId = glCreateShader(Gl_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &vertexShaderSrc, NULL);
	glCompileShader(vertexShaderId);
	GLuint success = 0;
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);





	const GLchar *vertexShaderSrc =
		"attribute vec3 in_Position;             " \
		"attribute vec4 in_Color;                " \
		"										 " \
		"varying vec4 ex_Color                   " \
		"                                        " \
		"void main()                             " \
		"{                                       " \
		"  gl_Position = vec4(in_Position, 1.0); " \
		"  ex_Color = inColor;                   " \
		"}                                       ";

	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &vertexShaderSrc, NULL);
	glCompileShader(vertexShaderId);
	GLint success = 0;
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		throw std::exception();
	}

	const GLchar *fragmentShaderSrc =
		"varying vec4 ex_Color;				" \
		"void main()                        " \
		"{                                  " \
		"  gl_FragColor = ex_Color;			" \
		"}                                  ";

	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &fragmentShaderSrc, NULL);
	glCompileShader(fragmentShaderId);
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		throw std::exception();
	}

	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	
	glBindAttribLocation(programId, 0, "in_Position");
	
	glLinkProgram(programId);
	glGetProgramiv(programId, GL_LINK_STATUS, &success);
	if (!success)
	{
		throw std::exception();
	}
	//getting the id for the shader
	GLint colorUniformId = glGetUniformLocation(programId, "in_Color");

	if (colorUniformId == -1)
	{
		throw std::exception();
	}

	glUseProgram(programId);
	glUniform4f(colorUniformId, 0, 1, 0, 1);
	glUseProgram(0);






	glDetachShader(programId, vertexShaderId);
	glDeleteShader(vertexShaderId);
	glDetachShader(programId, fragmentShaderId);
	glDeleteShader(fragmentShaderId);


	//while loop
  while(!quit)
  {
    SDL_Event event = {0};

    while(SDL_PollEvent(&event))
    {
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(programId);
		glBindVertexArray(vaoId);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(0);
		glUseProgram(0);

		SDL_GL_SwapWindow(window);









      if(event.type == SDL_QUIT)
      {
        quit = true;
      }
    }
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
