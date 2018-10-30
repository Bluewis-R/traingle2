#include "ShaderProgram.h"
#include "VertexArray.h"

#include "Texture.h"

ShaderProgram::ShaderProgram()
{
  //  getting the vertex data
  std::ifstream file("../shader/simple.vert");
  if (!file.is_open())
  {
    throw std::exception();
  }
  else
  {
    while (!file.eof())
    {
      std::string line;
      std::getline(file, line);
      vertShader += line + "\n";
    }
  }
  file.close();

  // getting the fragment data
  file.open("../shaders/simple.frag");
  if (!file.is_open())
  {
    throw std::exception();
  }
  else
  {
    while (!file.eof())
    {
      std::string line;
      std::getline(file, line);
      vertShader += line + "\n";
    }
    file.close();

    const char *vertex = vertShader.c_str();
    const char *fragment = fragShader.c_str();

    GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderId, 1, &vertex, NULL);
    glCompileShader(vertexShaderId);
    GLint success = 0;
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      throw std::exception();
    }

    GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderId, 1, &fragment, NULL);
    glCompileShader(fragmentShaderId);
    success = 0;
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      throw std::exception();

    }


    //  not sure if this goes here
    id = glCreateProgram();
    glAttachShader(id, vertexShaderId);
    glAttachShader(id, fragmentShaderId);
    glBindAttribLocation(id, 0, "in_Position");
    glBindAttribLocation(id, 1, "in_TexCoord");

    glLinkProgram(id);
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success)
    {
      throw std::exception();
    }

    glDetachShader(id, vertexShaderId);
    glDeleteShader(vertexShaderId);
    glDetachShader(id, fragmentShaderId);
    glDeleteShader(fragmentShaderId);
  }
}

ShaderProgram::ShaderProgram(std::string vert, std::string frag)
{
  //  getting the vertex data
  std::ifstream file(vert);
  if (!file.is_open())
  {
    throw std::exception();
  }
  else
  {
    while (!file.eof())
    {
      std::string line;
      std::getline(file, line);
      vertShader += line + "\n";
    }
  }
  file.close();

  // getting the fragment data
  file.open(frag);
  if (!file.is_open())
  {
    throw std::exception();
  }
  else
  {
    while (!file.eof())
    {
      std::string line;
      std::getline(file, line);
      fragShader += line + "\n";
    }
    file.close();

    const char *vertex = vertShader.c_str();
    const char *fragment = fragShader.c_str();

    GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderId, 1, &vertex, NULL);
    glCompileShader(vertexShaderId);
    GLint success = 0;
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      throw std::exception();
    }

    GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderId, 1, &fragment, NULL);
    glCompileShader(fragmentShaderId);
    success = 0;
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      throw std::exception();

    }


    //  not sure if this goes here
    id = glCreateProgram();
    glAttachShader(id, vertexShaderId);
    glAttachShader(id, fragmentShaderId);
    glBindAttribLocation(id, 0, "in_Position");
    glBindAttribLocation(id, 1, "in_TexCoord");

    glLinkProgram(id);
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success)
    {
      throw std::exception();
    }

    glDetachShader(id, vertexShaderId);
    glDeleteShader(vertexShaderId);
    glDetachShader(id, fragmentShaderId);
    glDeleteShader(fragmentShaderId);
  }
}

void ShaderProgram::draw(VertexArray * vertexArray)
{
  glUseProgram(id);
  glBindVertexArray(vertexArray->getId());

  glDrawArrays(GL_TRIANGLES, 0, 3);

  glBindVertexArray(0);
  glUseProgram(0);

}

void ShaderProgram::setUniform(std::string uniform, glm::vec4 value)
{
  GLuint uniformId = glGetUniformLocation(id, uniform.c_str());

  if (uniformId == -1)
  {
    throw std::exception();
  }

  glUseProgram(id);
  glUniform4f(uniformId, value.x, value.y, value.z, value.w);
  glUseProgram(0);
}

void ShaderProgram::setUniform(std::string uniform, float value)
{
  GLint uniformId = glGetUniformLocation(id, uniform.c_str());
  if (uniformId == -1)
  {
    throw std::exception();
  }

  glUseProgram(id);
  glUniform1f(uniformId, value);
  glUseProgram(0);
}

void ShaderProgram::setUniform(std::string uniform, glm::mat4 value)
{
	GLuint uniformId = glGetUniformLocation(id, uniform.c_str());

	if (uniformId == -1)
	{
		throw std::exception();
	}

	glUseProgram(id);
	glUniformMatrix4fv(uniformId, 1, GL_FALSE, glm::value_ptr(value));
	glUseProgram(0);
}

void ShaderProgram::setUniform(std::string uniform, int value)
{
	GLint uniformId = glGetUniformLocation(id, uniform.c_str());
	if (uniformId == -1)
	{
		throw std::exception();
	}

	glUseProgram(id);
	glUniform1i(uniformId, value);
	glUseProgram(0);
}

void ShaderProgram::setUniform(std::string uniform, Texture *texture)
{
	GLint uniformId = glGetUniformLocation(id, uniform.c_str());

	if (uniformId == -1)
	{
		throw std::exception();
	}

	for (size_t i = 0; i < samplers.size(); i++)
	{
		if (samplers.at(i).id == uniformId)
		{
			samplers.at(i).texture = texture;

			glUseProgram(id);
			glUniform1i(uniformId, i);
			glUseProgram(0);
			return;
		}
	}

	Sampler s;
	s.id = uniformId;
	s.texture = texture;
	samplers.push_back(s);

	glUseProgram(id);
	glUniform1i(uniformId, samplers.size() - 1);
	glUseProgram(0);
}


GLuint ShaderProgram::getId()
{
  return id;
}