#pragma once
#include "baselight.h"
#include "attenuation.h"
class PointLight :public BaseLight
{
public:
public:
	PointLight(const glm::vec3& color = glm::vec3(0, 0, 0), const glm::vec3& pos = glm::vec3(0, 0, 0), const float intensity = 1.0, const Attenuation& atten = Attenuation()):
	BaseLight(color,pos,intensity),m_attenuation(atten){}

	inline const Attenuation& getAttenuation() const { return m_attenuation; }

private:
	Attenuation m_attenuation;
};

