#pragma once
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "gl\freeglut.h"
#include "GLUTCallbacks.h"

class Texture2D
{

private:

	GLuint _ID; //TextureID
	int _width, _height;

public:

	Texture2D();
	~Texture2D();

	bool Load(char* path, int width, int height);

	GLuint GetID() const { return _ID; }
	int GetWidth() const { return _width; }
	int GetHeight() const { return _height; }

};
