#include "GameObject.h"

GameObject::GameObject(std::string texturePath, std::string OBJPath);
{
	m_texturePath = texturePath;
	m_objectPath = OBJPath;
	m_vertexArray = new VertexArray(OBJPath);
	m_tex = new Texture(m_texturePath);
}

GameObject::~GameObject()
{
}