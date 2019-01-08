#include <SDL2/SDL.h>

class GameObject;
class DeltaTime;
class Camera;

class Player
{
private:
	bool m_wKey_DOWN;
	bool m_dKey_DOWN;
	bool m_aKey_DOWN;
	bool m_sKey_DOWN;
	bool m_shiftKey_DOWN;
	bool m_spaceKey_DOWN;
	bool m_rightKey_DOWN;
	bool m_leftKey_DOWN;

	DeltaTime* m_deltaTime;
	GameObject* m_playerObject;
	Camera* m_camera;
public:
	Player(DeltaTime* _deltaTime, GameObject* _gameObject, Camera* _camera);
	void UpdateKeys();
	void Update();
	void CameraUpdate();
	void temp();
};