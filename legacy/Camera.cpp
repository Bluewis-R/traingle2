#include "Camera.h"

#include "ShaderProgram.h"

void Camera::Update(ShaderProgram* _shader)
{
	m_model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0, 1, 0));
	_shader->setUniform("in_View", glm::inverse(model));
}
