#include "PhysicsManager.h"

#include "GameObject.h"
#include "Physics.h"

void PhysicsManager::UpdatingThroughPhysicsObjets()
{
	for (int i = 0; i < m_physicsObjects.size(); i++)
	{
		for (int j = i + 1; i < m_physicsObjects.size(); j++)
		{
			std::string obj1 = m_physicsObjects.at(i)->GetPhysics()->GetColliderType();
			std::string obj2 = m_physicsObjects.at(j)->GetPhysics()->GetColliderType();
			//	sphere to sphere
			if (obj1 == "Sphere" && obj2 == "Sphere")
			{
				if (SphereToSphere(i, j)) 
				{
					m_physicsObjects.at(i)->GetPhysics()->CollisionUpdate(m_physicsObjects.at(j));
					m_physicsObjects.at(j)->GetPhysics()->CollisionUpdate(m_physicsObjects.at(i));
				}
			
			}
			//	box to box
			if (obj1 == "Box" && obj2 == "Box") {}
			//	Sphere to box
			if ((obj1 == "Sphere" && obj2 == "Box") || (obj1 == "Box" && obj2 == "Sphere")) {}




		}
	}
}

bool PhysicsManager::SphereToSphere(int _i, int _j)
{
	glm::vec3 i_pos = m_physicsObjects.at(_i)->GetPosition();
	glm::vec3 j_pos = m_physicsObjects.at(_j)->GetPosition();
	float i_radius = m_physicsObjects.at(_i)->GetPhysics()->GetSphereRadius();
	float j_radius = m_physicsObjects.at(_j)->GetPhysics()->GetSphereRadius();
	glm::vec3 dif = glm::vec3(i_pos.x - j_pos.x, i_pos.y - j_pos.y, i_pos.y - j_pos.y);
	float distance = sqrt(pow(dif.x, 2) + pow(dif.y, 2) + pow(dif.z, 2) );

	if (distance > i_radius + j_radius)
	{
		return true;
	}
	return false;
}