#include "light\spotlight.h"


SpotLight::SpotLight(const glm::vec3& color, const glm::vec3& pos, float intensity, const Attenuation& attenuation, float viewAngle) :
PointLight(color, pos, intensity, attenuation),
	m_cutoff(glm::cos(viewAngle / 2))
{
	
}

