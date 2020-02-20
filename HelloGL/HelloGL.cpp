#include "HelloGL.h"
#include "Cube.h"
#include "Pyramid.h"


HelloGL::HelloGL(int argc, char* argv[])
{
	HelloGL::InitGL(argc, argv);

	HelloGL::InitObjects();

	glutMainLoop();
}

void HelloGL::InitGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);

	//dont put before this
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("simple OpenGL Program");
	glutDisplayFunc(GLUTCallbacks::Display);

	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);

	glutKeyboardFunc(GLUTCallbacks::Keyboard);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	glViewport(0, 0, 800, 800);
	gluPerspective(45, 1, 0.1, 1000);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
}

void HelloGL::InitObjects()
{
	camera = new Camera();
	camera->eye.x = 0.0f; camera->eye.y = 0.0f; camera->eye.z = 1.0f;
	camera->center.x = 0.0f; camera->center.y = 0.0f; camera->center.z = 0.0f;
	camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;
	rotation = 0.0f;

	Mesh* cubeMesh = MeshLoader::LoadTextured((char*)"FileReader/cube.txt");
	Mesh* pyramidMesh = MeshLoader::LoadTextured((char*)"FileReader/pyramid.txt");

	Texture2D* texture = new Texture2D();
	texture->Load((char*)"RAW/Face.raw", 1024, 1024);

	for (int i = 0; i < (CUBENUM / 2); i++)
	{
		objects[i] = new Cube(cubeMesh, texture,((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f);	
	}

	for (int i = (CUBENUM / 2); i < CUBENUM; i++)
	{
		objects[i] = new Pyramid(pyramidMesh, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f);
	}
}

HelloGL::~HelloGL()
{
	delete camera;
	delete objects;
}

void HelloGL::Display()
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < CUBENUM; i++)
	{
		objects[i]->Draw();
	}
	glFlush();
	glutSwapBuffers();
}

void HelloGL::Update()
{
	glLoadIdentity();
	for (int i = 0; i < CUBENUM; i++)
	{
		objects[i]->Update();
	}
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);
	glutPostRedisplay();
	
	if (rotation >= 360.0f)
		rotation = 0.0f;
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{

	if (key == 'd')
		rotation += 5.0f;
	if (key == 'a')
		rotation -= 5.0f;
	if (key == 'k')
	{
		camera->eye.z++;
	}
	if (key == 'i')
	{
		camera->eye.z--;
	}
	if (key == 'l')
	{
		camera->eye.x++;

	}
	if (key == 'j')
	{
		camera->eye.x--;
	}
	if (key == 27)
	{
		exit(0);
	}
}


