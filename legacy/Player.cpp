#include "Player.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "GameObject.h"
#include "DeltaTime.h"
#include "Camera.h"

Player::Player(DeltaTime* _deltaTime, GameObject* _gameObject, Camera* _camera)
{
	m_playerObject = _gameObject;
	m_deltaTime = _deltaTime;
	m_camera = _camera;
}

void Player::UpdateKeys()						//	This updates the booleans for the player class
{
	SDL_Event event = { 0 };
	
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_w)						//  forward
			{
				m_wKey_DOWN = true;
			}
		
			if (event.key.keysym.sym == SDLK_s)						//  backward
			{
				m_sKey_DOWN = true;
			}
	
			if (event.key.keysym.sym == SDLK_a)						//  left
			{
				m_aKey_DOWN = true;
			}
		
			if (event.key.keysym.sym == SDLK_d)						//  right
			{
				m_dKey_DOWN = true;
			}

		}
		else if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_w)						//  forward
			{
				m_wKey_DOWN = false;
			}

			if (event.key.keysym.sym == SDLK_s)						//  backward
			{
				m_sKey_DOWN = false;
			}

			if (event.key.keysym.sym == SDLK_a)						//  left
			{
				m_aKey_DOWN = false;
			}

			if (event.key.keysym.sym == SDLK_d)						//  right
			{
				m_dKey_DOWN = false;
			}
		}
	}
	
}

void Player::temp()
{
	if (m_wKey_DOWN)
	{
		//float a = m_playerObject->GetPosition().y + (float)m_deltaTime->GetDeltaTime();

		m_playerObject->SetPosition(glm::vec3(0, 1, 0));
	}
}

void Player::Update()
{
	if (m_wKey_DOWN)
	{
		m_camera->SetPosition(glm::vec3(0.0f, m_camera->GetPosition().x + 1, 0.0f));
		std::cout << "y" << m_camera->GetPosition().y << std::endl;
	}
	




	m_camera->Update();
}


//copy of function
/*
void Player::UpdateKeys()						//	This updates the booleans for the player class
{
	SDL_Event event = { 0 };

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_w)						//  forward
			{
				m_wKey_DOWN = true;
			}

			else
			{
				m_wKey_DOWN = false;
			}

			if (event.key.keysym.sym == SDLK_s)						//  backward
			{
				m_sKey_DOWN = true;
			}
			else
			{
				m_sKey_DOWN = false;
			}

			if (event.key.keysym.sym == SDLK_a)						//  left
			{
				m_aKey_DOWN = true;
			}
			else
			{
				m_aKey_DOWN = false;
			}
			if (event.key.keysym.sym == SDLK_d)						//  right
			{
				m_dKey_DOWN = true;
			}
			else
			{
				m_dKey_DOWN = false;
			}
		}

		else if (event.type == SDL_KEYUP)

	}

}
*/