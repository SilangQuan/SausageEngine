#include "smesh.h"


SMesh::SMesh()
{
	VBO = INVALID_OGL_VALUE;
	EBO = INVALID_OGL_VALUE;
	VAO = INVALID_OGL_VALUE;
	numIndices = 0;
	materialIndex = INVALID_OGL_VALUE;
}


SMesh::~SMesh()
{
	if (VBO != INVALID_OGL_VALUE)
	{
		glDeleteBuffers(1, &VBO);
	}

	if (EBO != INVALID_OGL_VALUE)
	{
		glDeleteBuffers(1, &EBO);
	}

	if (VAO != INVALID_OGL_VALUE)
	{
		glDeleteVertexArrays(1, &VAO);
	}
}

void SMesh::init(const std::vector<VertexData>& vertices,
	const std::vector<unsigned int>& indices)
{
	numIndices = indices.size();

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(this->VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData)* vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)* numIndices, &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid*)(sizeof(glm::vec3)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid*)(sizeof(glm::vec2) + sizeof(glm::vec3)));

	glBindVertexArray(0);
}

void SMesh::setMaterialIndex(unsigned int index)
{
	materialIndex = index;
}

void SMesh::setNumIndices(unsigned int num)
{
	numIndices = num;
}

unsigned int  SMesh::getMaterialIndex() const
{
	return materialIndex;
}
unsigned int  SMesh::getNumIndices() const
{
	return numIndices;
}

GLuint  SMesh::getVBO() const
{
	return VBO;
}
GLuint  SMesh::getEBO() const
{
	return EBO;
}

GLuint SMesh::getVAO() const
{
	return VAO;
}

void SMesh::draw(ShaderProgram& shader)
{
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
