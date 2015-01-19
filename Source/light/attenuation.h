#pragma once
class Attenuation
{
public:
	Attenuation(){}
	Attenuation(float range, float constant, float linear, float quadratic) :
		m_range(range),
		m_constant(constant),
		m_linear(linear),
		m_quadratic(quadratic) {}

	inline float getRange() const { return m_range; }
	inline float getConstant() const { return m_constant; }
	inline float getLinear()   const { return m_linear; }
	inline float getQuadratic() const { return m_quadratic; }

private:
	float m_constant;
	float m_linear;
	float m_quadratic;
	float m_range;
};

