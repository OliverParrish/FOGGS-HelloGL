#include "SceneObject.h"

SceneObject::SceneObject(Mesh* mesh, Texture2D* texture)
{
	_mesh = mesh;

	_texture = texture;
}

SceneObject::~SceneObject()
{
	delete _mesh;
	delete _texture;
}

void SceneObject::Update()
{
}

void SceneObject::Draw()
{
}

void SceneObject::Keyboard(unsigned char key, int x, int y)
{
}
