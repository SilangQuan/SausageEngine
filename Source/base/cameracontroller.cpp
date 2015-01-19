#include "cameracontroller.h"


CameraController::CameraController(Camera *c)
{
	camera = c;
}


CameraController::~CameraController()
{
}

bool CameraController::keyPressEvent(QKeyEvent* event)
{
	switch (event->key())
	{
	case Qt::Key_W:

	break;
	case Qt::Key_S:
	break;
	case  Qt::Key_A:
	break;
	case Qt::Key_D:
	break;
	default:
		break;
	}
	return false;
}

bool CameraController::mouseMoveEvent(QMouseEvent *e)
{
	return false;
}