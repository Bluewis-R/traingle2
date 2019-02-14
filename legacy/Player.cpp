#include "Player.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "GameObject.h"
#include "SimplePhysics.h"
#include "DeltaTime.h"
#include "Camera.h"
#include "ObjectManager.h"

Player::Player(DeltaTime* _deltaTime, GameObject* _gameObject, Camera* _camera)
{
	m_playerObject = _gameObject;
	m_deltaTime = _deltaTime;
	m_camera = _camera;
}

void Player::AddPlatform(Group* _platform)
{
	m_platform = _platform;
}

//	This updates the booleans for the player class to avoid
//	the wierd window intteratction with the triple press thing.
void Player::UpdateKeys()						
{
	SDL_Event event = { 0 };
	
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_w)
			{
				m_wKey_DOWN = true;
			}		
			if (event.key.keysym.sym == SDLK_s)
			{
				m_sKey_DOWN = true;
			}	
			if (event.key.keysym.sym == SDLK_a)
			{
				m_aKey_DOWN = true;
			}		
			if (event.key.keysym.sym == SDLK_d)
			{
				m_dKey_DOWN = true;
			}
			if (event.key.keysym.sym == SDLK_SPACE)
			{
				m_spaceKey_DOWN = true;
			}
			if (event.key.keysym.sym == SDLK_LSHIFT)
			{
				m_shiftKey_DOWN = true;
			}
			if (event.key.keysym.sym == SDLK_RIGHT)
			{
				m_rightKey_DOWN = true;
			}
			if (event.key.keysym.sym == SDLK_LEFT)
			{
				m_leftKey_DOWN = true;
			}

		}
		else if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_w)
			{
				m_wKey_DOWN = false;
			}
			if (event.key.keysym.sym == SDLK_s)
			{
				m_sKey_DOWN = false;
			}
			if (event.key.keysym.sym == SDLK_a)
			{
				m_aKey_DOWN = false;
			}
			if (event.key.keysym.sym == SDLK_d)
			{
				m_dKey_DOWN = false;
			}
			if (event.key.keysym.sym == SDLK_SPACE)
			{
				m_spaceKey_DOWN = false;
			}
			if (event.key.keysym.sym == SDLK_LSHIFT)
			{
				m_shiftKey_DOWN = false;
			}
			if (event.key.keysym.sym == SDLK_RIGHT)
			{
				m_rightKey_DOWN = false;
			}
			if (event.key.keysym.sym == SDLK_LEFT)
			{
				m_leftKey_DOWN = false;
			}
		}
	}
	
}

//	This function moves the camera dependand to the input keys.
void Player::Update()
{
	//	Degbugging controls
	glm::vec3 currentPos = m_camera->GetPosition();
	glm::vec3 currentRot = m_camera->GetRotation();
	float dt = (float)m_deltaTime->GetDeltaTime()/1000.0f;

	//	This was used for debugging
	if (false)
	{
		if (m_wKey_DOWN)
		{
			m_camera->SetPosition(glm::vec3(currentPos.x, currentPos.y, currentPos.z - 3 * dt));
		}
		if (m_sKey_DOWN)
		{
			m_camera->SetPosition(glm::vec3(currentPos.x, currentPos.y, currentPos.z + 3 * dt));
		}
		if (m_aKey_DOWN)
		{
			m_camera->SetPosition(glm::vec3(currentPos.x - 3 * dt, currentPos.y, currentPos.z));
		}
		if (m_dKey_DOWN)
		{
			m_camera->SetPosition(glm::vec3(currentPos.x + 3 * dt, currentPos.y, currentPos.z));
		}
		if (m_shiftKey_DOWN)
		{
			m_camera->SetPosition(glm::vec3(currentPos.x, currentPos.y - 3 * dt, currentPos.z));
		}
		if (m_spaceKey_DOWN)
		{
			m_camera->SetPosition(glm::vec3(currentPos.x, currentPos.y + 3 * dt, currentPos.z));
		}
		if (m_rightKey_DOWN)
		{
			m_camera->SetRotation(glm::vec3(currentRot.x, currentRot.y - dt, currentRot.z));
		}
		if (m_leftKey_DOWN)
		{
			m_camera->SetRotation(glm::vec3(currentRot.x, currentRot.y + dt, currentRot.z));
		}
	}

	//	If the player is on the ground and the player in holding space
	//	he is force of the ground. If the space bar is down the gravity
	//	is less and the player falls slower.
	if (m_spaceKey_DOWN) { m_playerObject->GetPhysics()->SetGravity(25.0f); }
	else { m_playerObject->GetPhysics()->SetGravity(90.0f); }
	if (m_spaceKey_DOWN && !(m_playerObject->GetPhysics()->GetAirborn()))
	{
  	m_playerObject->GetPhysics()->SetVelocity(glm::vec3(0.0f, 40.0f,0.0f));
		glm::vec3 oldPos = m_playerObject->GetPosition();
		glm::vec3 newPos = oldPos + (m_playerObject->GetPhysics()->GetVelocity() * ((float)m_deltaTime->GetDeltaTime()) / 1000.0f);

		m_playerObject->SetPosition(newPos);
		m_playerObject->GetPhysics()->SetAirborn(true);
	}

	//	Adds a slight rotation to the camera left and right.
	float angle = 0.2f * sin(0.001f * SDL_GetTicks());
	m_camera->SetRotation(glm::vec3(0.0f, angle, 0.0f));
	

	//	Shows the damage effect to the cameat as well as removing the
	//	score from the player.
	if (!m_playerObject->GetPhysics()->GetAirborn() && m_platform->m_currentObj->GetDeathState())
	{
		m_score = 0.0f;
		m_camera->SetRotation(glm::vec3(0.05f * sin((rand() % 20)*0.05), 0.0f, 0.0f));

	}
	
	//	Score updating and displaying.
	m_score += m_deltaTime->GetDeltaTime() / 1000.0f;
	if (m_score > m_highscore) { m_highscore = m_score; }
	system("CLS");
	std::cout << "Highscore : " << (int)m_highscore << std::endl;
	std::cout << "  Score   : " << (int)m_score;

	//	Camera update.
	m_camera->Update();
}