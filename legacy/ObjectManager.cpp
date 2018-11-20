#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::UpdatePhysics()
{
}

void ObjectManager::UpdateDraw()
{
}

void ObjectManager::AddObject(std::string _name, std::string _OBJpath, std::string _TEXpath)
{
	GameObject* temp = new GameObject(_OBJpath, _TEXpath);
	m_GObjects.push_back(temp);
	//delete temp;
	//new GameObject(_OBJpath, _TEXpath)
}
