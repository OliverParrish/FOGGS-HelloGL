#include "HelloGL.h"
#include "Cube.h"
#include "Pyramid.h"
#include "MeshLoader.h"

#include <ft2build.h>
#include FT_FREETYPE_H

HelloGL::HelloGL(int argc, char* argv[])
{
	HelloGL::InitGL(argc, argv);

	HelloGL::InitObjects();

	HelloGL::InitLighting();

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
	glutCreateWindow("Bad 3D Stuff");
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
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
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

	Mesh* cubeMesh = MeshLoader::LoadTextured((char*)"FileReader/NewCube.txt");
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

void HelloGL::InitLighting()
{
	_lightPosition = new Vector4();
	_lightPosition->x = 0.0;
	_lightPosition->y = 0.0;
	_lightPosition->z = 1.0;
	_lightPosition->w = 0.0;

	_lightData = new Lighting();
	_lightData->Ambient.x = 0.2;
	_lightData->Ambient.y = 0.2;
	_lightData->Ambient.z = 0.2;
	_lightData->Ambient.w = 1.0;
	_lightData->Diffuse.x = 0.8;
	_lightData->Diffuse.y = 0.8;
	_lightData->Diffuse.z = 0.8;
	_lightData->Diffuse.w = 1.0;
	_lightData->Specular.x = 0.2;
	_lightData->Specular.y = 0.2;
	_lightData->Specular.z = 0.2;
	_lightData->Specular.w = 1.0;

}

void HelloGL::DrawString(const char* text, Vector3* position, Color color)
{
	glPushMatrix();

	glTranslatef(position->x, position->y, position->z);
	glRasterPos2f(0.0f, 0.0f);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)text);

	glPopMatrix();
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

	Vector3 v = {0.25f, 0.70f, -1.0f };
	Color c = { 0.0f, 1.0f, 0.0f };

	HelloGL::DrawString("Bad 3D Game", &v, c);
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

	glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->Ambient.x));
	glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightPosition->x));

	
	if (rotation >= 360.0f)
		rotation = 0.0f;
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	for (int i = 0; i < CUBENUM; i++)
	{
		objects[i]->Keyboard(key, x, y);
	}

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


