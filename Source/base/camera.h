#ifndef CAMERA_H
#define CAMERA_H
#include "common.h"
#include <QtOpenGL>
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
class Camera
{
public:
	Camera();
	~Camera();
	Camera(const glm::vec3& pos, const glm::vec3& target, const glm::vec3& up);
	void setPerspectiveParameter(float left, float right, float bottom, float top, float nearValue, float farValue, bool perspective = true);
	void setPerspectiveParameter(float fov, float aspect, float nearValue, float farValue);
	void setViewMatrix(const glm::mat4& viewMatrix);
	void setProjectionMatrix(const glm::mat4& projectionMatrix);
	const glm::mat4& getViewMatrix() const { return m_viewMatrix; }
	const glm::mat4& getPerspectiveMatrix() const { return m_projectionMatrix; }
	const glm::vec3 getPos(){ return m_pos; }

private:
	glm::vec3 m_pos;
	glm::vec3 m_target;
	glm::vec3 m_up;
	glm::mat4x4 m_viewMatrix;
	glm::mat4x4 m_projectionMatrix;
	
};

#endif // CAMERA_H
