#ifndef VERTEXDATA_H
#define VERTEXDATA_H
#include "glm/glm.hpp"
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
struct VertexData
{
    VertexData();
    VertexData(glm::vec3 pos);
	VertexData(glm::vec3 pos, glm::vec2 texCoord);
	VertexData(glm::vec3 pos, glm::vec2 texCoord, glm::vec3 normal);

	glm::vec3 position;
	glm::vec2 texCoord;
	glm::vec3 normalLine;
	glm::vec3 tangent;

   // int boneId[4];
   // float boneWeight[4];
};

#endif // VERTEXDATA_H
