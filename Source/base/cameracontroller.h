#pragma once
#include "common.h"
#include "base/camera.h"

class CameraController
{
public:
	CameraController(Camera *camera);
	~CameraController();
	bool mouseMoveEvent(QMouseEvent *e);
    bool keyPressEvent(QKeyEvent* e);

private:
	Camera *camera;
	glm::mat4 accumulateRotation;

};

