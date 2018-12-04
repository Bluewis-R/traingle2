#include "Player.h"

void Player::UpdateKeys(SDL_Event &_event)						//	This updates the booleans for the player class
{
	while (SDL_PollEvent(&_event))
	{
		if (_event.type == SDL_KEYDOWN)
		{
			if (_event.key.keysym.sym == SDLK_w)						//  forward
			{
				m_wKey_DOWN = true;
			}
			else
			{
				m_wKey_DOWN = false;
			}

			if (_event.key.keysym.sym == SDLK_s)						//  backward
			{
				m_sKey_DOWN = true;
			}
			else
			{
				m_sKey_DOWN = false;
			}
			if (_event.key.keysym.sym == SDLK_a)						//  left
			{
				m_aKey_DOWN = true;
			}
			else
			{
				m_aKey_DOWN = false;
			}
			if (_event.key.keysym.sym == SDLK_d)						//  right
			{
				m_dKey_DOWN = true;
			}
			else
			{
				m_dKey_DOWN = false;
			}



		}


	}

}
