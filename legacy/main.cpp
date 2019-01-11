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
#include "Physics.h"
#include "PhysicsManager.h"
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

  //	Defining Objects
  ShaderProgram* shaderProgram = new ShaderProgram("simple.vert", "simple.frag");
  ObjectManager* objectManager = new ObjectManager(shaderProgram);
  objectManager->AddObject("skybox", "res/skybox.png", "res/skybox.obj");
	objectManager->AddObject("sp", "res/earth.png", "res/sphere.obj");
	objectManager->AddObject("sp2", "res/earth.png", "res/sphere.obj");
	objectManager->AddObject("sp3", "res/earth.png", "res/sphere.obj");
	
	objectManager->AddObject("Floor", "res/re_hall_diffuse.png", "res/plane.obj");


  GameObject* playerModel = new GameObject("res/curuthers_diffuse.png", "res/curuthers.obj");
  //	camera
  Camera* camera = new Camera(shaderProgram, dTime);
  //	Player
  Player* player = new Player(dTime, playerModel, camera);
	//	Physics

	//	Setting up scene
	objectManager->Edit("skybox")->SetScale(glm::vec3(20.0f, 20.0f, 20.0f));
	objectManager->Edit("sp")->SetPhysics(dTime);
	objectManager->Edit("sp2")->SetPhysics(dTime);
	objectManager->Edit("sp3")->SetPhysics(dTime);
	objectManager->Edit("sp")->SetPosition(glm::vec3(0.0f, 3.5f, 3.0f));
	objectManager->Edit("sp2")->SetPosition(glm::vec3(3.0f, 3.5f, 0.0f));
	objectManager->Edit("sp3")->SetPosition(glm::vec3(-3.0f, 3.0f, 1.0f));

	objectManager->Edit("sp2")->GetPhysics()->SetForce(glm::vec3(-100.0f, 0.0f, 0.0f));
	objectManager->Edit("sp3")->GetPhysics()->SetForce(glm::vec3(100.0f, 0.0f, 0.0f));

	
	objectManager->Edit("Floor")->SetPhysics(dTime);
	objectManager->Edit("Floor")->GetPhysics()->SetStatic(true);
	objectManager->Edit("Floor")->SetPosition(glm::vec3(0.0f, -2.0f, 0.0f));
	objectManager->Edit("Floor")->SetScale(glm::vec3(50.0f, 1.0f, 50.0f));
	objectManager->Edit("Floor")->GetPhysics()->SetColliderType("Plane");




	PhysicsManager* physicsManager = new PhysicsManager(objectManager);

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
		
		physicsManager->UpdatingThroughPhysicsObjets();



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
	delete physicsManager;
	delete camera;
	delete player;
	delete playerModel;


  SDL_DestroyWindow(window);
  SDL_Quit();



  return 0;
}