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
#include "Camera.h"
#include "DeltaTime.h"
#include "ObjectManager.h"
#include "GameObject.h"
#include "Player.h"

//class Player;

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
	//	deltaTime
	DeltaTime* dTime = new DeltaTime();

  //	objectmanager
  ShaderProgram* shaderProgram = new ShaderProgram("simple.vert", "simple.frag");
  ObjectManager* objectManager = new ObjectManager(shaderProgram);
  //objectManager->AddObject("skybox", "res/skybox.png", "res/skybox.obj");
  objectManager->AddObject("hall", "res/re_hall_diffuse.png", "res/re_hall_baked.obj");
  objectManager->AddObject("obj2", "res/re_hall_diffuse.png", "res/object2.obj");
  //objectManager->AddObject("cat", "res/curuthers_diffuse.png", "res/curuthers.obj");
  GameObject* playerModel = new GameObject("res/curuthers_diffuse.png", "res/curuthers.obj");
  //	camera
  Camera* camera = new Camera(shaderProgram, dTime);
  //	Player
  Player* player = new Player(dTime, playerModel, camera);




  /*
  VertexArray *hallShape = new VertexArray("re_hall_baked.obj");
  Texture *hallTexture = new Texture("re_hall_diffuse.png");
  VertexArray *shape = new VertexArray("curuthers.obj");
  Texture *texture = new Texture("curuthers.png");
  */
  
  float angle = 0;
  
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);

	//while loop
  for(bool quit = false; !quit;)
  {
		//	updates the keys of the player
		player->UpdateKeys();
		//	Setting the Initial time for the loop
		dTime->SetInitialTime();
		
		player->Update();
		camera->Update();








	SDL_GetWindowSize(window, &windowWidth, &windowHeight);
	glViewport(0, 0, windowWidth, windowHeight);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	shaderProgram->setUniform("in_Projection", glm::perspective(glm::radians(45.0f),
		(float)windowWidth / (float)windowHeight, 0.1f, 100.f));

	//	Shader
	shaderProgram->setUniform("in_Emissive", glm::vec3(0, 0.1, 0));
	shaderProgram->setUniform("in_Ambient", glm::vec3(0.4, 0.3, 0.3));
	objectManager->UpdateDraw();

	// Create a "camera"
	camera->Update();
	/*
	glm::mat4 model(1.0f);
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0, 1, 0));
	shaderProgram->setUniform("in_View", glm::inverse(model));
	*/

	/*

	// Create a "camera"
	glm::mat4 model(1.0f);
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0, 1, 0));
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

	*/


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

	//	DeltaTime calculation
	dTime->CalculateDeltaTime();



	angle += 0.2f;
    
	SDL_GL_SwapWindow(window);
  }

  delete objectManager;
	delete camera;
  SDL_DestroyWindow(window);
  SDL_Quit();



  return 0;
}