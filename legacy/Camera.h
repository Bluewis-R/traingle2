#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>

class ShaderProgram;
class DeltaTime;

class Camera
{
private:
	ShaderProgram* m_shader;
	DeltaTime* m_dtime;
	glm::mat4 m_model;

	glm::vec3 m_position = glm::vec3(0.0f, 3.0f, 15.0f);
	glm::vec3 m_rotation = glm::vec3(0.0f, 45.0f, 0.0f);
	
public:
	Camera(ShaderProgram* _shader, DeltaTime* _deltaTime);
	void SetPosition(glm::vec3 _pos) { m_position = _pos; }
	glm::vec3 GetPosition() { return m_position; }
	void SetRotation(glm::vec3 _rot) { m_rotation = _rot; }
	glm::vec3 GetRotation() { return m_rotation; }
	void Update();

};