#pragma once
#include "common.h"

class BaseLight
{
public:
	BaseLight(const glm::vec3& color, const glm::vec3& pos,  float intensity) :
		m_color(color),
		m_pos(pos),
		m_intensity(intensity) {}

	inline glm::vec3 getPos() const  {return m_pos;}
	inline float getIntensity() { return m_intensity; }
	inline glm::vec3 getColor() { return m_color; }
	inline void setPos(const glm::vec3& newPos){ m_pos = newPos; }

private:
	glm::vec3    m_color;
	glm::vec3 m_pos;
	float      m_intensity;
};

