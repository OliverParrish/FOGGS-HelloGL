#pragma once
#include "SceneObject.h"
class Pyramid : public SceneObject
{
private:

	GLfloat _rotation;
	Vector3 _position;
	float rotationSpeed;

public:
	Pyramid(Mesh* mesh, float x, float y, float z);
	~Pyramid();

	void Draw();
	void Update();

	void Keyboard(unsigned char key, int x, int y);
};

