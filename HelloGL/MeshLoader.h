#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "gl\freeglut.h"
#include "Structures.h"

namespace MeshLoader
{
	Mesh* Load(char* path);
	Mesh* LoadTextured(char* path);
};

