#include "Camera.h"



Camera::Camera()
{
	setupProjectionMatrix(45.0f, 0.1f, 100.0f, projection);
	view = Matrix4D();
}

void Camera::setupProjectionMatrix(const float angleOfView, const float near, const float far, Matrix4D& m)
{
	
	//Replace 3.14 with actual PI sometime
	float scale = 1 / tan(angleOfView * 0.5 * 3.14 / 180);
	m.set(0, scale);
	m.set(5, scale);
	m.set(10, -far / (far - near));
	m.set(14, -far * near / (far - near));
	m.set(11, -1);
	m[15] = 1;

}

void Camera::moveLeft(float newSpeed)
{
	speed = newSpeed;
	view = view * view.translate(Vector4D(speed, 0, 0, 1));
}

void Camera::moveRight(float newSpeed)
{
	speed = newSpeed;
	view = view * view.translate(Vector4D(-speed, 0, 0, 1));
}

void Camera::moveUp(float newSpeed)
{
	speed = newSpeed;
	view = view * view.translate(Vector4D(0, -speed, 0, 1));
}

void Camera::moveDown(float newSpeed)
{
	speed = newSpeed;
	view = view * view.translate(Vector4D(0, speed, 0, 1));
}

void Camera::moveBack(float newSpeed)
{
	speed = newSpeed;
	view = view * view.translate(Vector4D(0, 0, -speed, 1));
}
void Camera::moveForward(float newSpeed)
{
	speed = newSpeed;
	view = view * view.translate(Vector4D(0, 0, speed, 1));
}
//Without setting new speed
void Camera::moveLeft()
{
	view = view * view.translate(Vector4D(speed, 0, 0, 1));
}

void Camera::moveRight()
{
	view = view * view.translate(Vector4D(-speed, 0, 0, 1));
}

void Camera::moveUp()
{
	view = view * view.translate(Vector4D(0, -speed, 0, 1));
}

void Camera::moveDown()
{
	view = view * view.translate(Vector4D(0, speed, 0, 1));
}

void Camera::moveBack()
{
	view = view * view.translate(Vector4D(0, 0, -speed, 1));
}
void Camera::moveForward()
{
	view = view * view.translate(Vector4D(0, 0, speed, 1));
}

void Camera::setSpeed(float newSpeed)
{
	speed = newSpeed;
}
