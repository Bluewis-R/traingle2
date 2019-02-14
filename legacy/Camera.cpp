#include "Camera.h"

#include "ShaderProgram.h"
#include "DeltaTime.h"

Camera::Camera(ShaderProgram* _shader, DeltaTime* _deltaTime)
{
	m_shader = _shader;
	m_dtime = _deltaTime;
}

void Camera::Update()
{
	m_model = glm::mat4(1.0f);
	m_model = glm::rotate(m_model, m_rotation.x, glm::vec3(1, 0, 0));
	m_model = glm::rotate(m_model, m_rotation.y, glm::vec3(0, 1, 0));
	m_model = glm::rotate(m_model, m_rotation.z, glm::vec3(0, 0, 1));
	m_model = glm::translate(m_model, m_position);
	m_shader->setUniform("in_View", glm::inverse(m_model));
}