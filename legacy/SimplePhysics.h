#include <glm/glm.hpp>
#include <glm/ext.hpp>

class GameObject;
class DeltaTime;

class SimplePhysics
{
private:
	DeltaTime* m_deltaTime;
	GameObject* m_gameObject;
	glm::vec3 m_velocity;

	float m_gravity;
	bool m_airborn;


public:
	SimplePhysics(GameObject* _gameObject, DeltaTime* _deltaTime);
	void UpdatePhysics();
	void SetVelocity(glm::vec3 _vel) { m_velocity = _vel; }
	glm::vec3 GetVelocity() { return m_velocity; }
	void SetAirborn(bool _bool) { m_airborn = _bool; }
	bool GetAirborn() { return m_airborn; }

	void SetGravity(float _gravity) { m_gravity = _gravity; }



};