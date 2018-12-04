#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Camera
{
private:
	glm::mat4 m_model;


public:
	void Update(ShaderProgram* _shader);

};