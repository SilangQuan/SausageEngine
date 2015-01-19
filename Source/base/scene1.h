#pragma once
#include <vector>
#include <QDebug>
#include <QTimer>
#include <QObject>
#include "light/pointlight.h"
#include "shader/shaderprogram.h"

class Scene:QObject
{
	Q_OBJECT
public:
	Scene();
	~Scene();
	void addLight(PointLight* pLight);
	void setShader(ShaderProgram *pShader);
	void setUniform();

private:
	
	std::vector<PointLight * > pointLights;
	ShaderProgram *shaderProgram;
	QTimer *updateTimer;

private slots:
	void update();
};

