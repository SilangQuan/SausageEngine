#include "vertexdata.h"

VertexData::VertexData()
{
	this->position = glm::vec3(0, 0, 0);
	this->texCoord = glm::vec2(0, 0);
	this->normalLine = glm::vec3(0, 0, 0);
  //  for(int i =0 ;i<4;i++) {boneId[i]=0;boneWeight[i]=0.25;}
}

VertexData::VertexData(glm::vec3  pos)
{
    this->position = pos;
   // for(int i =0 ;i<4;i++) {boneId[i]=0;boneWeight[i]=0.25;}
}

VertexData::VertexData(glm::vec3  pos, glm::vec2 texCoord)
{
    this->position=pos;
    this->texCoord=texCoord;
	this->normalLine = glm::vec3(0, 0, 0);
 //   for(int i =0 ;i<4;i++) {boneId[i]=0;boneWeight[i]=0.25;}
}

VertexData::VertexData(glm::vec3  pos, glm::vec2 texCoord, glm::vec3  normal)
{
    this->position=pos;
    this->texCoord=texCoord;
    this->normalLine=normal;
   // for(int i =0 ;i<4;i++) {boneId[i]=0;boneWeight[i]=0.25;}
}
