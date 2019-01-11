#include "ObjectManager.h"
#include "GameObject.h"

ObjectManager::ObjectManager(ShaderProgram* _shader)
{
	m_shader = _shader;
}

ObjectManager::~ObjectManager()
{
	for (std::vector< GameObject* >::iterator it = m_GObjects.begin(); it != m_GObjects.end(); ++it)
	{
		delete (*it);
	}
	m_GObjects.clear();
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
	temp->SetName(_name);
	m_GObjects.push_back(temp);
	

	//delete temp;
	//new GameObject(_OBJpath, _TEXpath)
}

GameObject* ObjectManager::Edit(std::string _string)
{
	for (int i = 0; i < m_GObjects.size(); i++)
	{
		if (m_GObjects.at(i)->GetName() == _string)
		{
			return m_GObjects.at(i);
		}
	}
}