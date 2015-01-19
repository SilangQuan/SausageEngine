#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include <QDebug>
#include <QTimer>
#include <QObject>
#include "light/pointlight.h"
#include "shader/shaderprogram.h"
#include <QObject>

class Scene : public QObject
{
	Q_OBJECT

public:
	Scene(QObject *parent = 0);
	~Scene();
	void addLight(PointLight* pLight);
	void setShader(ShaderProgram *pShader);
	void setUniform();

private:

	std::vector<PointLight * > pointLights;
	ShaderProgram *shaderProgram;
	QTimer *updateTimer;

	private slots:
	void updateLight();
	
signals:
	void updateScene();
};

#endif // SCENE_H
