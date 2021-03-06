#pragma once


#include "core/app.h"
#include "GLFW/glfw3.h"
#include "Matrix4D.h"
#include "Vector4D.h"

class Camera {
public:

	Matrix4D view;
	Matrix4D projection;

	Camera();
	//Sets up projection from fov, near and far plane.
	void setupProjectionMatrix(const float angleOfView, const float near, const float far, Matrix4D& m);
	//moveas around a point and rotates toward it 
	void lookat(float radius);

	//moves the view around
	void moveLeft(float speed);
	void moveRight(float speed);
	void moveUp(float speed);
	void moveDown(float speed);

};


