#include <vector>
#include <string>


#include "glm/glm.hpp"
#include "glm/ext.hpp"


class ObjectManager;
class GameObject;
class Physics;

class PhysicsManager
{
private:
	std::vector<GameObject*> m_physicsObjects;


public:
	PhysicsManager(ObjectManager* _objectManager);
	~PhysicsManager();
	void AddToPhysicsObjects(GameObject* _gameObject) { m_physicsObjects.push_back(_gameObject); }

	void UpdatingThroughPhysicsObjets();
	bool SphereToSphere(int _i, int _j, glm::vec3& _cp);
	bool SphereToPlane(int _i, int _j, glm::vec3& _cp);
	
};

namespace Util
{
	float DistanceToPlane(const glm::vec3& p, const glm::vec3& q, const glm::vec3& n);
	
	bool STS(const glm::vec3& c0, const glm::vec3& c1, float r1, float r2, glm::vec3& cp);

}