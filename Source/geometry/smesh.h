#pragma once
#include "common.h"
#include <vector>
#include "base/vertexdata.h"
#include "shader/shaderprogram.h"

class SMesh
{
public:
	SMesh();
	~SMesh();
	void init(const std::vector<VertexData>& Vertices,
		const std::vector<unsigned int>& Indices);
	void draw(ShaderProgram &shader);
	void setMaterialIndex(unsigned int index);
	unsigned int getMaterialIndex() const;
	void setNumIndices(unsigned int num);
	unsigned int getNumIndices() const;

	GLuint getVAO() const;
	GLuint getVBO() const;
	GLuint getEBO() const;
	

private:
	std::vector<VertexData> vertices;

	//For vertex buffer
	GLuint VAO,VBO;
	//For index buffer
	GLuint EBO;
	unsigned int numIndices;
	unsigned int materialIndex;
};

