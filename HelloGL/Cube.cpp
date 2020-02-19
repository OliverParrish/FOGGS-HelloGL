#include "Cube.h"
#include "Structures.h"
#include <fstream>
#include <iostream>

Cube::Cube(Mesh* mesh, float x, float y, float z) : SceneObject(mesh)
{
	rotationSpeed = rand() % 5 + 0.5f;
	_rotation = rand() % 90;

	_position.x = x;
	_position.y = y;
	_position.z = z;
}

Cube::~Cube()
{

}

void Cube::Draw()
{
	if (_mesh->Vertices !=nullptr && _mesh->Colors !=nullptr && _mesh->Indices !=nullptr)
	{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
	glColorPointer(3, GL_FLOAT, 0, _mesh->Colors);

	glPushMatrix();

	glTranslatef(_position.x, _position.y, _position.z);
	glRotatef(_rotation, rotationSpeed, rotationSpeed, rotationSpeed);

	glDrawElements(GL_TRIANGLES, _mesh->IndexCount, GL_UNSIGNED_SHORT, _mesh->Indices);
	glPopMatrix();

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	}
}

void Cube::Update()
{
	_rotation += rotationSpeed;

	if (_rotation >= 360)
		_rotation = 0;

	_position.z += 0.5f;
	if (_position.z >= 5.0f)
	{
		_position.z = -50.0f;
	}
}
