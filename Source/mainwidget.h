#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "common.h"
#include <QGLWidget>
#include <QString>
#include <QFileInfo>
#include <QtGui>
#include <QtOpenGL>
#include <QDebug>
#include "light/directionlight.h"
#include "light/pointlight.h"
#include "light/spotlight.h"

#include "base/camera.h"
#include "geometry/entity.h"
#include "shader/shaderprogram.h"
#include "base/scene.h"


class MainWidget : public QGLWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

	bool fileExists(const QString& filePath);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL( int width, int height );
	void compileShader();
	void setUniform();
	void initScene();

private:
	void checkGlError(const char *s);
	Scene* scene;
	Camera* mainCamera;
	PointLight *pointLight;
	glm::mat4 modelMatrix;
	glm::mat4 viewMatrix;
	ShaderProgram prog;
	GLuint vertexArrayID;
	GLuint vertexbuffer;
	GLuint normalbuffer;
	Entity objModel;
};

#endif // MAINWIDGET_H
