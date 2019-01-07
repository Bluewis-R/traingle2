#include "GameObject.h"

#include "ShaderProgram.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Physics.h"

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

void GameObject::Update(ShaderProgram* _shader)
{
	
	m_model = glm::mat4(1.0f);
	m_model = glm::translate(m_model, m_position);
	m_model = glm::rotate(m_model, m_rotation.x, glm::vec3(1, 0, 0));
	m_model = glm::rotate(m_model, m_rotation.y, glm::vec3(0, 1, 0));
	m_model = glm::rotate(m_model, m_rotation.z, glm::vec3(0, 0, 1));
	_shader->setUniform("in_Model", m_model);
	_shader->setUniform("in_Texture", m_texture);
	_shader->draw(m_vertexArray);
	
}