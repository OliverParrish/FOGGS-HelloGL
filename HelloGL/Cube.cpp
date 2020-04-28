#include "Cube.h"
#include "Structures.h"
#include "MeshLoader.h"
#include <fstream>
#include <iostream>

Cube::Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z) : SceneObject(mesh, texture)
{
	rotationSpeed = rand() % 5 + 0.5f;
	_rotation = rand() % 90;

	_position.x = x;
	_position.y = y;
	_position.z = z;
	_mesh = mesh;
}

Cube::~Cube()
{

}

void Cube::Draw()
{
	if (_mesh->Vertices != nullptr && _mesh->Normals != nullptr && _mesh->Indices != nullptr && _mesh->TexCoords != nullptr)
	{
		glBindTexture(GL_TEXTURE_2D, _texture->GetID());

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnable(GL_NORMAL_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, _mesh->Vertices);
		glNormalPointer(GL_FLOAT, 0, _mesh->Normals);

		glTexCoordPointer(2, GL_FLOAT, 0, _mesh->TexCoords);

		//call ambient, diffuse, specular, and Shininess light effects
		_material = new Material();
		_material->Ambient.x = 0.8; _material->Ambient.y = 0.05; _material->Ambient.z = 0.05;
		_material->Ambient.w = 1.0;
		_material->Diffuse.x = 0.8; _material->Diffuse.y = 0.05; _material->Diffuse.z = 0.05;
		_material->Diffuse.w = 1.0;
		_material->Specular.x = 1.0; _material->Specular.y = 1.0; _material->Specular.z = 1.0;
		_material->Specular.w = 1.0;
		_material->Shininess = 100.0f;

		glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->Ambient.x));
		glMaterialf(GL_FRONT, GL_SHININESS, _material->Shininess);

		glPushMatrix();

		glTranslatef(_position.x, _position.y, _position.z);
		glRotatef(_rotation, rotationSpeed, rotationSpeed, rotationSpeed);

		glDrawElements(GL_TRIANGLES, _mesh->IndexCount, GL_UNSIGNED_SHORT, _mesh->Indices);
		glPopMatrix();

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}

void Cube::Update()
{
	/*_rotation += rotationSpeed;*/

	if (_rotation >= 360)
		_rotation = 0;
	else if (_rotation <= -360)
		_rotation = 0;

	_position.z += 0.5f;
	if (_position.z >= 5.0f)
	{
		_position.z = -50.0f;
	}
}

void Cube::Keyboard(unsigned char key, int x, int y)
{
		//allows player rotation of pyramids
		if (key == 'd')
			_rotation += rotationSpeed;
		if (key == 'a')
			_rotation -= rotationSpeed;
}
