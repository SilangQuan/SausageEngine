#pragma once
#include "pointlight.h"
class SpotLight :public PointLight
{
public:
public:
	SpotLight(const glm::vec3& color = glm::vec3(0, 0, 0), const glm::vec3& pos = glm::vec3(0, 0, 0), float intensity = 0, const Attenuation& atten = Attenuation(), float viewAngle = 170.0);

	inline float getCutoff() const { return m_cutoff; }
private:
	float m_cutoff;
};

