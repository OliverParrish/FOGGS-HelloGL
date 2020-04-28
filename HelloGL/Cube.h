#pragma once
#include "SceneObject.h"


class Cube : public SceneObject
{
private:
	
	GLfloat _rotation;
	Vector3 _position;
	float rotationSpeed;

public:
	Cube(Mesh* mesh, Texture2D* texture, float x, float y, float z);
	~Cube();

	void Draw();
	void Update();

	void Keyboard(unsigned char key, int x, int y);

};
