#include "Pyramid.h"


Pyramid::Pyramid(Mesh* mesh, float x, float y, float z) : SceneObject(mesh, nullptr)
{
	rotationSpeed = rand() % 5 + 0.5f;
	_rotation = rand() % 90;

	_position.x = x;
	_position.y = y;
	_position.z = z;
}

Pyramid::~Pyramid()
{
}

void Pyramid::Draw()
{
	if (_mesh->Vertices != nullptr && _mesh->Normals != nullptr && _mesh->Indices != nullptr)
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
		glColorPointer(3, GL_FLOAT, 0, _mesh->Normals);

		glPushMatrix();

		glTranslatef(_position.x, _position.y, _position.z);
		glRotatef(_rotation, rotationSpeed, rotationSpeed, rotationSpeed);

		glDrawElements(GL_TRIANGLES, _mesh->IndexCount, GL_UNSIGNED_SHORT, _mesh->Indices);
		glPopMatrix();

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
} 

void Pyramid::Update()
{

	if (_rotation >= 360)
		_rotation = 0;
	else if (_rotation <= -360)
	{
		_rotation = 0;
	}
}

void Pyramid::Keyboard(unsigned char key, int x, int y)
{
	//allows player rotation of pyramids
	if (key == 'd')
		_rotation += rotationSpeed;
	if (key == 'a')
		_rotation -= rotationSpeed;
}
