#include <SDL2/SDL.h>

class Player
{
private:
	bool m_wKey_DOWN;
	bool m_dKey_DOWN;
	bool m_aKey_DOWN;
	bool m_sKey_DOWN;


public:
	void UpdateKeys(SDL_Event &_event);

};