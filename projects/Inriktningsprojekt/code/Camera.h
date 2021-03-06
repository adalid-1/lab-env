#pragma once


#include "core/app.h"
#include "GLFW/glfw3.h"
#include "Matrix4D.h"
#include "Vector4D.h"

class Camera {
public:

	Matrix4D view;
	Matrix4D projection;

	void setSpeed(float newSpeed);
	float speed = 0.5;

	Camera();
	//Sets up projection from fov, near and far plane.
	void setupProjectionMatrix(const float angleOfView, const float near, const float far, Matrix4D& m);

	//translating camera pos
	void moveLeft(float newSpeed);
	void moveRight(float newSpeed);
	void moveUp(float newSpeed);
	void moveDown(float newSpeed);
	void moveBack(float newSpeed);
	void moveForward(float newSpeed);
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void moveBack();
	void moveForward();
	//moveas around a point and rotates toward it 
	void lookat(float radius);

	void rotateView(float angleX, float angleY); 
};


