#pragma once
#include "baselight.h"
#
class DirectionLight :public BaseLight
{
public:
	DirectionLight(const glm::vec3& color = glm::vec3(0, 0, 0), const glm::vec3& pos = glm::vec3(0, 0, 0), float intensity = 0);
};

