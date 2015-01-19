#include "camera.h"

Camera::Camera()
{

}


Camera::~Camera()
{

}

Camera::Camera(const glm::vec3& pos, const glm::vec3& target, const glm::vec3& up)
{
	m_pos = pos;
	m_target = target;
	m_up = up;

	m_viewMatrix = glm::lookAt(pos, target, up);
}

void Camera::setViewMatrix(const glm::mat4& viewMatrix)
{
	m_viewMatrix = viewMatrix;
}

void Camera::setProjectionMatrix(const glm::mat4& projectionMatrix)
{
	m_projectionMatrix = projectionMatrix;
}

void Camera::setPerspectiveParameter(float left, float right, float bottom,float top, float nearValue, float farValue, bool perspective /* = true */)
{
	if (perspective)
	{
		m_projectionMatrix = glm::frustum(left, right, bottom, top, nearValue, farValue);
	}
	else{
		m_projectionMatrix = glm::ortho(left, right, bottom, top, nearValue, farValue);
	}
}

void Camera::setPerspectiveParameter(float fov, float aspect, float nearValue, float farValue)
{
	m_projectionMatrix = glm::perspective(fov, aspect, nearValue, farValue);
}