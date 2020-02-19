#pragma once
#include "SceneObject.h"


class Cube : public SceneObject
{
private:
	
	GLfloat _rotation;
	Vector3 _position;
	float rotationSpeed;

public:
	Cube(Mesh* mesh, float x, float y, float z);
	~Cube();

	void Draw();
	void Update();

};
