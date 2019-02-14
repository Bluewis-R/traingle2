#include <vector>
#include <string>
#include <iostream>
#include <random>

class DeltaTime;
class GameObject;
class ShaderProgram;
class PhysicsManager;

struct Group
{
	std::string m_name;
	std::vector<GameObject*> m_objects;
	GameObject* m_currentObj;
};

class ObjectManager
{
private:
	
	ShaderProgram* m_shader;
	PhysicsManager* m_physicsManager;

	std::vector<GameObject*> m_GObjects;
	std::vector<Group*> m_groups;
	DeltaTime* m_deltaTime;
	

public:
	ObjectManager(ShaderProgram* _shader, DeltaTime* _deltaTime);
	~ObjectManager();
	
	void UpdateDraw();
	int NumberOfObjects() { return m_GObjects.size(); }
	GameObject* GetGameObject(int _i) { return m_GObjects.at(_i); }
	void AddObject(std::string _name, std::string _TEXpath, std::string _OBJpath);
	GameObject* Edit(std::string _string);
	void GOdelete(GameObject* _gameObject);

	void NewGroup(std::string _string, GameObject* _obj);
	Group* GetGroup(std::string _string);
	void AddToGroup(GameObject* _gameObject, std::string _group);
	GameObject* CreateRandomPlatform();

	void PlatformCode();
};