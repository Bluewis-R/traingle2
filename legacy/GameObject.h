#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <string>

class Texture;
class VertexArray;
class ShaderProgram;
class SimplePhysics;
class DeltaTime;
struct Group;

class GameObject
{
private:
	std::string m_name, m_texturePath, m_objectPath;

	glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 m_size = glm::vec3(1.0f, 1.0f, 1.0f);
	Texture* m_texture;
	VertexArray* m_vertexArray; 
	SimplePhysics* m_physics;
	glm::mat4 m_model;

	bool m_deathState = false;

	Group* m_platform;

public:
	GameObject(std::string texturePath, std::string OBJPath);
	~GameObject();
	void SetPosition(glm::vec3 pos) { m_position = pos; }
	void SetRotation(glm::vec3 rot) { m_rotation = rot; }
	void SetScale(glm::vec3 scale) { m_scale = scale; }
	void SetName(std::string _name) { m_name = _name; }
	void SetSize(glm::vec3 _size) { m_size = _size; }
	void SetDeathState(bool _bool) { m_deathState = _bool; }
	bool GetDeathState() { return m_deathState; }
	glm::vec3 GetPosition() { return m_position; };
	glm::vec3 GetRotation() { return m_rotation; };
	glm::vec3 GetScale() { return m_scale; };
	std::string GetName() { return m_name; }
	glm::vec3 GetSize() { return m_size; };

	SimplePhysics* GetPhysics() { return m_physics; }
	void SetPhysics(DeltaTime* _dTime);

	

	void Update(ShaderProgram* _shader);
};
