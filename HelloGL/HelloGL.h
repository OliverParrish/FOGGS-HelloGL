#pragma once
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "gl\freeglut.h"
#include "GLUTCallbacks.h"
#include "Structures.h"
#include "Cube.h"
#define REFRESHRATE 16
#define CUBENUM 200

class HelloGL
{
public:
	HelloGL(int argc, char* argv[]);

	~HelloGL(void);

	void Display();

	void Update();

	void Keyboard(unsigned char key, int x, int y);

	void InitObjects();

	void InitLighting();

	void DrawString(const char* text, Vector3* position, Color color);

	void InitGL(int argc, char* argv[]);

private:

	float rotation;

	Camera* camera;
	
	SceneObject* objects[CUBENUM];

	Vector4* _lightPosition;
	Lighting* _lightData;
};




