#include "Camera.h"



Camera::Camera()
{
	setupProjectionMatrix(45.0f, 0.1f, 100.0f, projection);
	view = Matrix4D();
}

void Camera::setupProjectionMatrix(const float angleOfView, const float near, const float far, Matrix4D& m)
{
	float scale = 1 / tan(angleOfView * 0.5 * 3.14 / 180);
	m.set(0, scale);
	m.set(5, scale);
	m.set(10, -far / (far - near));
	m.set(14, -far * near / (far - near));
	m.set(11, -1);
	m[15] = 1;
}


void Camera::lookat(float radius)
{

	//move around target
	float camX = sin(glfwGetTime()) * radius;
	float camZ = cos(glfwGetTime()) * radius;
	Vector4D lookFrom(camX, 0, camZ, 1);
	Vector4D target(0, 0, 0, 1);

	//rotate towards target
	Vector4D hyp = target - lookFrom;
	float angle = atan2(hyp[0], hyp[2]);
	view = view.RotationY(-angle) * view.translate(lookFrom);
}

void Camera::moveLeft(float speed)
{
	view = view * view.translate(Vector4D(speed, 0, 0, 1));
}

void Camera::moveRight(float speed)
{
	view = view * view.translate(Vector4D(-speed, 0, 0, 1));
}

void Camera::moveUp(float speed)
{
	view = view * view.translate(Vector4D(0, -speed, 0, 1));
}

void Camera::moveDown(float speed)
{
	view = view * view.translate(Vector4D(0, speed, 0, 1));
}


