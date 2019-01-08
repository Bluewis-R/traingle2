#include <vector>
#include <string>

class GameObject;
class Physics;

class PhysicsManager
{
private:
	std::vector<GameObject*> m_physicsObjects;


public:
	void AddToPhysicsObjects(GameObject* _gameObject) { m_physicsObjects.push_back(_gameObject); }

	void UpdatingThroughPhysicsObjets();
	bool SphereToSphere(int _i, int _j);

};