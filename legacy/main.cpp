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
#include "SimplePhysics.h"
#include "GameObject.h"
#include "Player.h"


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

  //	Defining Objects
  ShaderProgram* shaderProgram = new ShaderProgram("simple.vert", "simple.frag");
  ObjectManager* objectManager = new ObjectManager(shaderProgram, dTime);
  objectManager->AddObject("skybox", "res/skybox.png", "res/skybox.obj");
	objectManager->AddObject("sp", "res/water.png", "res/cube.obj");
	objectManager->AddObject("Player", "res/boat.png", "res/boat.obj");

	GameObject* pl = objectManager->Edit("Player");
	// Groups
	objectManager->NewGroup("Platforms", objectManager->Edit("sp"));
	GameObject* l = objectManager->Edit("sp");
	objectManager->AddToGroup(l, "Platforms");

  GameObject* playerModel = new GameObject("res/curuthers_diffuse.png", "res/curuthers.obj");
  Camera* camera = new Camera(shaderProgram, dTime);
  Player* player = new Player(dTime, pl, camera);
	player->AddPlatform(objectManager->GetGroup("Platforms"));

	//	Setting up scene
	objectManager->Edit("skybox")->SetScale(glm::vec3(20.0f, 20.0f, 20.0f));

	objectManager->Edit("Player")->SetPhysics(dTime);
	objectManager->Edit("Player")->SetPosition(glm::vec3(0.0f, 50.0f, 0.0f));
	objectManager->Edit("Player")->SetRotation(glm::vec3(0.0f, -80.0f, 0.0f));
	objectManager->Edit("Player")->SetScale(glm::vec3(0.015f, 0.015f, 0.015f));

	objectManager->Edit("sp")->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
	objectManager->Edit("sp")->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	objectManager->Edit("sp")->SetSize(glm::vec3(1.0f, 1.0f, 1.0f));

	


  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
	
	//
	//while loop
	//
  for(bool quit = false; !quit;)
  {
		//	updates the keys of the player.
		player->UpdateKeys();
		//	Setting the Initial time for the loop.
		dTime->SetInitialTime();
		

		objectManager->PlatformCode();
		objectManager->Edit("Player")->GetPhysics()->UpdatePhysics();


		player->Update();
		camera->Update();





	SDL_GetWindowSize(window, &windowWidth, &windowHeight);
	glViewport(0, 0, windowWidth, windowHeight);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	shaderProgram->setUniform("in_Projection", glm::perspective(glm::radians(45.0f),
		(float)windowWidth / (float)windowHeight, 0.1f, 100.f));


	//	Shader.
	shaderProgram->setUniform("in_Emissive", glm::vec3(0.1, 0.1, 0.1));
	shaderProgram->setUniform("in_Ambient", glm::vec3(0.1, 0.1, 0.1));
	shaderProgram->setUniform("in_LightPos", glm::vec3(15, 45, 0.0));
	

	
	
	//	Rendering all objects.
	objectManager->UpdateDraw();
	//	Camera update.
	camera->Update();









	//	DeltaTime calculation.
	dTime->CalculateDeltaTime();


    
	SDL_GL_SwapWindow(window);
  }

	//	Safe Deletion.
  delete objectManager;
	delete camera;
	delete camera;
	delete player;
	delete playerModel;


  SDL_DestroyWindow(window);
  SDL_Quit();



  return 0;
}



