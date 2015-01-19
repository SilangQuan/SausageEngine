#include "scene.h"


Scene::Scene()
{
	updateTimer = new QTimer();
	updateTimer->setInterval(30);
	connect(updateTimer, SIGNAL(timeout()), this, SLOT(update()));
}


Scene::~Scene()
{
	for (int i = 0; i < pointLights.size(); i++)
	{
		delete pointLights[i];
	}
}

void Scene::addLight(PointLight* pLight)
{
	pointLights.push_back(pLight);
}

void Scene::setUniform()
{
	char tmp[100];
	int count = static_cast<int>(pointLights.size());
	shaderProgram->setUniform("pointLightCount", count);
	for (int i = 0; i < count; i++)
	{
		sprintf(tmp, "pointLights[%d].pos", i);
		shaderProgram->setUniform(tmp, pointLights[i]->getPos());
		sprintf(tmp, "pointLights[%d].color", i);
		shaderProgram->setUniform(tmp, pointLights[i]->getColor());
		sprintf(tmp, "pointLights[%d].intensity", i);
		shaderProgram->setUniform(tmp, pointLights[i]->getIntensity());
		sprintf(tmp, "pointLights[%d].constant", i);
		shaderProgram->setUniform(tmp, pointLights[i]->getAttenuation().getConstant());
		sprintf(tmp, "pointLights[%d].linear", i);
		shaderProgram->setUniform(tmp, pointLights[i]->getAttenuation().getLinear());
		sprintf(tmp, "pointLights[%d].quadratic", i);
		shaderProgram->setUniform(tmp, pointLights[i]->getAttenuation().getQuadratic());
		sprintf(tmp, "pointLights[%d].range", i);
		shaderProgram->setUniform(tmp, pointLights[i]->getAttenuation().getRange());
	}

}

void Scene::setShader(ShaderProgram *pShader)
{
	shaderProgram = pShader;
}

void Scene::update()
{
	glm::mat4 transMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 2, 0));
	glm::mat4 rotationX = glm::rotate(transMatrix, 1.8f, glm::vec3(1, 0, 0));
	glm::mat4 rotationY = glm::rotate(transMatrix, 1.8f, glm::vec3(0, 1, 0));
	glm::mat4 rotationZ = glm::rotate(transMatrix, 1.8f, glm::vec3(0, 0, 1));


	glm::vec4  newPos = glm::vec4(pointLights[0]->getPos(), 1.0f) * rotationX;
	pointLights[0]->setPos(glm::vec3(newPos));

	newPos = glm::vec4(pointLights[0]->getPos(), 1.0f) * rotationY;
	pointLights[1]->setPos(glm::vec3(newPos));

	newPos = glm::vec4(pointLights[0]->getPos(), 1.0f) * rotationZ;
	pointLights[2]->setPos(glm::vec3(newPos));

	this->setUniform();
}