#include <glm/glm.hpp>
#include <vector>

class VertexBuffer
{
private:
	GLuint id;
	int componants;
	std::vector <GLfloat> data;
	bool dirty;

public:
	VertexBuffer();

	void add(glm::vec3 value);
	void add(glm::vec4 value);
	
	int GetComponants();
	int GetDataSize();
	GLuint GetId();
};