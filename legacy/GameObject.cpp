#include "GameObject.h"

GameObject::GameObject(std::string texturePath, std::string OBJPath)
{
	m_texturePath = texturePath;
	m_objectPath = OBJPath;
	m_vertexArray = new VertexArray(OBJPath);
	m_texture = new Texture(m_texturePath);
}

GameObject::~GameObject()
{
	delete m_texture;
	delete m_vertexArray;
}

GameObject::Update()
{
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0, -2.1f, -20.0f));
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0, 1, 0));
	shaderProgram->setUniform("in_Model", model);
	shaderProgram->setUniform("in_Texture", texture);
	shaderProgram->draw(shape);

}