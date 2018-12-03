#include "ObjectManager.h"
#include "GameObject.h"

ObjectManager::ObjectManager(ShaderProgram* _shader)
{
	m_shader = _shader;
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::UpdatePhysics()
{
	// for if physics is enabeled ->

}

void ObjectManager::UpdateDraw()
{
	for (int i = 0; i < m_GObjects.size(); i++)
	{
		m_GObjects.at(i)->Update(m_shader);
	}

}

void ObjectManager::AddObject(std::string _name, std::string _TEXpath, std::string _OBJpath)
{
	GameObject* temp = new GameObject(_TEXpath, _OBJpath);
	m_GObjects.push_back(temp);
	//delete temp;
	//new GameObject(_OBJpath, _TEXpath)
}