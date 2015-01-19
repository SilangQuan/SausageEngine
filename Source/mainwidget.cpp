#include "mainwidget.h"
#include <QFileInfo>

MainWidget::MainWidget(QWidget *parent)
    : QGLWidget(parent)
{
	this->setMinimumSize(640 ,  480);

}

MainWidget::~MainWidget()
{

}

void MainWidget::checkGlError(const char *s)
{
	GLenum err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cout << "OpenGL Error :" << s << endl;
	}
}

void MainWidget::compileShader()
{
	if (!prog.compileShaderFromFile("../Assets/shader/multipleLights.vert", GLSLShader::VERTEX))
	{
		printf("Vertex shader failed to compile!\n%s",
			prog.log().c_str());
		exit(1);
	}
	if (!prog.compileShaderFromFile("../Assets//shader/multipleLights.frag", GLSLShader::FRAGMENT))
	{
		printf("Fragment shader failed to compile!\n%s",
			prog.log().c_str());
		exit(1);
	}

	prog.bindAttribLocation(0, "VertexPosition");
	prog.bindAttribLocation(1, "VertexNormal");
	prog.bindAttribLocation(2, "VertexNormal");
	if (!prog.link())
	{
		printf("Shader program failed to link!\n%s",
			prog.log().c_str());
		exit(1);
	}
	if (!prog.validate())
	{
		printf("Program failed to validate!\n%s",
			prog.log().c_str());
		exit(1);
	}
	prog.use();
}

void MainWidget::initializeGL()
{
	checkGlError("before glew");
	if (glewInit() != GLEW_OK)
	{
		qDebug() << "glew Init failed";
		exit(EXIT_FAILURE);
	}
	checkGlError("after glew");
	qDebug("GL Version: %s", glGetString(GL_VERSION));
	qDebug("GLSL version:%s", glGetString(GL_SHADING_LANGUAGE_VERSION));

    glShadeModel( GL_SMOOTH );
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    glClearDepth( 1.0 );
	glEnable(GL_CULL_FACE);
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
	
	initScene();
}

void MainWidget::resizeGL(int width, int height)
{
	glViewport(0, 0, (GLint)width, (GLint)height);
	// Calculate aspect ratio
	float aspect = float(width) / float(height ? height : 1);

	const float zNear = 0.01, zFar = 100.0, fov = 45.0;

	// Reset projection
	mainCamera->setPerspectiveParameter(fov, aspect, zNear, zFar);
	prog.setUniform("MVP", mainCamera->getPerspectiveMatrix() * mainCamera->getViewMatrix() * modelMatrix);
}

void MainWidget::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	objModel.render();
}

bool MainWidget::fileExists(const QString & filePath)
{
	QFileInfo file(filePath);
	return file.exists();
}

void MainWidget::setUniform()
{
	glm::mat4 mv = mainCamera->getViewMatrix() * modelMatrix;

	//prog.setUniform("ModelViewMatrix", mv);
	//prog.setUniform("NormalMatrix", glm::mat3(glm::vec3(mv[0]), glm::vec3(mv[1]), glm::vec3(mv[2])));
	prog.setUniform("MVP", mainCamera->getPerspectiveMatrix() * mv);
	prog.setUniform("materialInfo.diffuse", glm::vec3(0.9f, 0.5f, 0.3f));
	prog.setUniform("ambient", 0.1f, 0.1f, 0.1f);
	prog.setUniform("materialInfo.specular", 0.8f, 0.8f, 0.8f);
	prog.setUniform("materialInfo.shininess", 100.0f);
	scene->setUniform();

	prog.setUniform("cameraPosition", mainCamera->getPos());
}

void MainWidget::initScene()
{
	// Calculate aspect ratio
	float aspect = float(width()) / float(height() ? height() : 1);
	const float zNear = 0.01, zFar = 100.0, fov = 45.0;

	// Set projection
	mainCamera = new Camera(glm::vec3(0, 5, 20), glm::vec3(0, 3, 0), glm::vec3(0.0, 1.0, 0.0));
	mainCamera->setPerspectiveParameter(fov, aspect, zNear, zFar);
	modelMatrix = glm::mat4(1.0f);

	scene = new Scene();
	connect(scene, SIGNAL(updateScene()), this, SLOT(update()));
	scene->setShader(&prog);

	PointLight *pointLight1 = new PointLight(glm::vec3(0, 1, 0), glm::vec3(0, 2, 3), 1.8, Attenuation(20, 0.1, 0.22, 0.20));
	PointLight *pointLight2 = new PointLight(glm::vec3(1, 0, 0), glm::vec3(3, 2, 0), 1.8, Attenuation(20, 0.1, 0.22, 0.20));
	PointLight *pointLight3 = new PointLight(glm::vec3(0, 0, 1), glm::vec3(-3, 2, 0), 1.8, Attenuation(20, 0.1, 0.22, 0.20));

	scene->addLight(pointLight1);
	scene->addLight(pointLight2);
	scene->addLight(pointLight3);

	compileShader();
	setUniform();
	objModel.loadFromFile("../Assets/model/bio.obj");
	objModel.setShader(prog);
}
