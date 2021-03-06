#include "Camera.h"



Camera::Camera()
{
	setupProjectionMatrix(45.0f, 0.1f, 100.0f, projection);
	view = Matrix4D();
}

void Camera::setupProjectionMatrix(const float angleOfView, const float near, const float far, Matrix4D& m)
{
	float scale = 1 / tan(angleOfView * 0.5 * 3.14159 / 180);
	m.set(0, scale);
	m.set(5, scale);
	m.set(10, -far / (far - near));
	m.set(11, -1);
	m.set(14, -far * near / (far - near));
	m[15] = 0.3;
}

void Camera::lookat(float radius) {
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

void Camera::rotateView(float angleX, float angleY) {

	view = view.RotationY(angleX) * view.RotationX(-angleY) * view;
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
	view = view.translate(Vector4D(speed, 0, 0, 1)) * view;
}

void Camera::moveRight()
{
	view = view.translate(Vector4D(-speed, 0, 0, 1)) * view;
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
	view = view.translate(Vector4D(0, 0, -speed, 1)) * view;
}
void Camera::moveForward()
{
	view = view.translate(Vector4D(0, 0, speed, 1)) * view;
}

void Camera::setSpeed(float newSpeed)
{
	speed = newSpeed;
}
