#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Texture.h"
#include "VertexArray.h"
#include "String.h"
#include <glm/>


class GameObject
{
private:
	std::string m_name, m_texturePath, m_objectPath;

	glm::vec3 m_position = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 m_rotation = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
	Texture* m_texture;
	VertexArray* m_vertexArray; 
	//Physics* m_physics;

	glm::mat4(1.0f) model;

public:
	GameObject(std::string texturePath, std::string OBJPath);
	~GameObject();
	void SetPosition(glm::vec3 pos) { m_position = pos; }
	void SetRotation(glm::vec3 rot) { m_rotation = rot; }
	void SetScale(glm::vec3 scale) { m_scale = scale; }
	glm::vec3 GetPosition() { return m_position; };
	glm::vec3 GetRotation() { return m_rotation; };
	glm::vec3 GetScale() { return m_scale; };

	void Update();
};