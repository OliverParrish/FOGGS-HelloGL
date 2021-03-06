#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include "Texture2D.h"

class SceneObject
{
protected:

	Mesh* _mesh;
	Texture2D* _texture;

public:

	SceneObject(Mesh* mesh, Texture2D* texture);
	virtual ~SceneObject();

	virtual void Update();
	virtual void Draw();

	virtual void Keyboard(unsigned char key, int x, int y);

};
