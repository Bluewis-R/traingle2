#include "ObjectManager.h"
#include "GameObject.h"
#include "DeltaTime.h"
#include "PhysicsManager.h"

//	Constructor things
ObjectManager::ObjectManager(ShaderProgram* _shader, DeltaTime* _deltaTime)
{
	srand(time((unsigned)NULL));
	m_shader = _shader;
	m_deltaTime = _deltaTime;
}
 
ObjectManager::~ObjectManager()
{
	for (std::vector< GameObject* >::iterator it = m_GObjects.begin(); it != m_GObjects.end(); ++it)
	{
		delete (*it);
	}
	m_GObjects.clear();

	for (std::vector< Group* >::iterator it = m_groups.begin(); it != m_groups.end(); ++it)
	{
		delete (*it);
	}
}

void ObjectManager::UpdateDraw()
{
	for (int i = 0; i < m_GObjects.size(); i++)
	{
		m_GObjects.at(i)->Update(m_shader);
	}
}

//	This adds an object to the main GameObject vector
void ObjectManager::AddObject(std::string _name, std::string _TEXpath, std::string _OBJpath)
{
	GameObject* temp = new GameObject(_TEXpath, _OBJpath);
	temp->SetName(_name);
	m_GObjects.push_back(temp);
}

//	This finds and returns a GameObject with the same name
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

//	This deletes a pointer from the main vector of all GameObjects
void ObjectManager::GOdelete(GameObject* _gameObject)
{
	for (int i = 0; i < m_GObjects.size(); i++)
	{
		if (m_GObjects.at(i) == _gameObject)
		{
			m_GObjects.erase(m_GObjects.begin()+i);
		}
	}

}

//	Groups
//
//
//
void ObjectManager::NewGroup(std::string _string, GameObject* _obj)
{
	m_groups.push_back(new Group());
	m_groups.back()->m_name = _string;
	m_groups.back()->m_currentObj = _obj;
}

//	Adds a GameObject to  specific group
void ObjectManager::AddToGroup(GameObject* _gameObject, std::string _group)
{
	for (int i = 0; i < m_groups.size(); i++)
	{
		if (m_groups.at(i)->m_name == _group)
		{
			m_groups.at(i)->m_objects.push_back(_gameObject);
		}
	}
}

//	Returns a group from the list of groups
Group* ObjectManager::GetGroup(std::string _string)
{
	for (int i = 0; i < m_groups.size(); i++)
	{
		if (m_groups.at(i)->m_name == _string)
		{
			return m_groups.at(i);
		}
	}
}


//	CODE FOR PLatforms
//
//
void ObjectManager::PlatformCode()
{
	Group* g = GetGroup("Platforms");
	float dt = m_deltaTime->GetDeltaTime() / 1000.0f;

	for (int i = 0; i < g->m_objects.size(); i++)
	{
		GameObject* obj = g->m_objects.at(i);
		
		//	If the moving object is left of the screen
		//	delete the object.
		if (obj->GetPosition().x< -2.0f)
		{			
			g->m_objects.erase(g->m_objects.begin());
			GOdelete(obj);
		}

		//	if the Object outside of the screen on the left
		//	enters the screen, create a new obejct th the left.
		if (g->m_objects.back()->GetPosition().x < 1.0f)
		{
			GameObject* newObj = CreateRandomPlatform();
			float tempx = ((g->m_objects.back()->GetSize().x) + (newObj->GetSize().x)) / 2;
			
			glm::vec3 lastPos = g->m_objects.back()->GetPosition();
			float test = lastPos.x + tempx;
			
			newObj->SetPosition(glm::vec3(test, 0.0f, 0.0f));
			
			g->m_objects.push_back(newObj);
		}

		//	Determins what the type of cube is below the object.
		if (g->m_currentObj->GetPosition().x < -0.5f)
		{
			g->m_currentObj = g->m_objects.at(2);
		}

		//	movement of the platforms
		obj->SetPosition(obj->GetPosition() + glm::vec3(-dt, 0.0f, 0.0f) );
	}

}

GameObject* ObjectManager::CreateRandomPlatform()
{
	std::vector<std::string> textures = { "res/water.png", "res/moss.png" };
	std::vector<std::string> objects = { "res/cube.obj",  "res/cube.obj" };
	std::vector<bool> deathState = {false, true};
	std::vector<glm::vec3> sizes = { glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f) };
	int i = rand() % (textures.size());
	GameObject* temp = new GameObject(textures.at(i), objects.at(i));
	temp->SetSize(sizes.at(i));
	temp->SetDeathState(deathState.at(i));


	m_GObjects.push_back(temp);
	return temp;
}