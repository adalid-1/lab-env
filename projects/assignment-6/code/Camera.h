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

	void lookat(float radius) {
		//float tid = glfwGetTime();
		
		float camX = sin(glfwGetTime()) * radius;
		float camZ = cos(glfwGetTime())* radius;
		Vector4D lookFrom(camX, 0, camZ, 1);

		//Might want to be able to choose target 
		Vector4D target(0, 0, 0, 1);

		//rotate towards target
		Vector4D hyp = target - lookFrom;
		float a = atan2(hyp[0], hyp[2]);

		view = view.RotationY(-a) * view.translate(lookFrom);
	}
};


