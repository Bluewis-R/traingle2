#include <vector>
#include <string>
//#include "GameObject.h"

class GameObject;
class ShaderProgram;

class ObjectManager
{
private:
	std::vector<GameObject*> m_GObjects;
	ShaderProgram* m_shader;
public:
	ObjectManager(ShaderProgram* _shader);
	~ObjectManager();
	void UpdatePhysics();
	void UpdateDraw();
	int NumberOfObjects() { return m_GObjects.size(); }
	GameObject* GetGameObject(int _i) { return m_GObjects.at(_i); }
	void AddObject(std::string _name, std::string _TEXpath, std::string _OBJpath);
	GameObject* Edit(std::string _string);
};