#include "directionlight.h"


DirectionLight::DirectionLight(const glm::vec3& color, const glm::vec3& pos, float intensity) :
	BaseLight(color, pos, intensity)
{
}

