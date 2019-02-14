#include "GameObject.h"

#include "ShaderProgram.h"
#include "Texture.h"
#include "VertexArray.h"
#include "SimplePhysics.h"
#include "DeltaTime.h"


//	Constructor things
GameObject::GameObject(std::string texturePath, std::string OBJPath)
{
	m_texturePath = texturePath;
	m_objectPath = OBJPath;
	m_vertexArray = new VertexArray(OBJPath);
	m_texture = new Texture(m_texturePath);
}

//	Avoiding memory errors.
GameObject::~GameObject()
{
	delete m_texture;
	delete m_vertexArray;
	delete m_physics;
}

//	The Update funciton for all of the objects in the project.
void GameObject::Update(ShaderProgram* _shader)
{
	m_model = glm::mat4(1.0f);
	m_model = glm::translate(m_model, m_position);
	m_model = glm::rotate(m_model, m_rotation.x, glm::vec3(1, 0, 0));
	m_model = glm::rotate(m_model, m_rotation.y, glm::vec3(0, 1, 0));
	m_model = glm::rotate(m_model, m_rotation.z, glm::vec3(0, 0, 1));
	m_model *= glm::vec4(m_scale, 1.0f);
	_shader->setUniform("in_Model", m_model);
	_shader->setUniform("in_Texture", m_texture);
	_shader->draw(m_vertexArray);
	
}

//	Sets the NULL pointer to a working physics class.
void GameObject::SetPhysics(DeltaTime* _dTime)
{
	m_physics = new SimplePhysics(this, _dTime);
}
