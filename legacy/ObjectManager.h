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

	void AddObject(std::string _name, std::string _TEXpath, std::string _OBJpath);

};