#pragma once

#include <vector>
#include <string>
#include "GameObject.h"


class ObjectManager
{
private:
	std::vector<GameObject*> m_GObjects;

public:
	ObjectManager();
	~ObjectManager();
	void UpdatePhysics();
	void UpdateDraw();

	void AddObject(std::string _name, std::string _OBJpath, std::string _TEXpath);

};