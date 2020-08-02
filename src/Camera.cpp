#include "Camera.h"

#include "glm/gtx/transform.hpp"

#include <iostream>

const float UNIT_MOVEMENT = 0.25;
const float MOUSE_SENSITIVITY = 0.003;

Camera &Camera::instance()
{
    static Camera *instance = new Camera();
    return *instance;
}

void Camera::mouseLook(int mouseX, int mouseY)
{
    // TODO: Which vector are you modifying?
    if (oldMousePosition.x == 0 && oldMousePosition.y == 0)
    {
        oldMousePosition.x = mouseX;
        oldMousePosition.y = mouseY;
        return;
    }

    float xdiff = mouseX - oldMousePosition.x;
    float ydiff = mouseY - oldMousePosition.y;

    oldMousePosition.x = mouseX;
    oldMousePosition.y = mouseY;

    viewDirection.x += xdiff * MOUSE_SENSITIVITY;
    viewDirection.y -= ydiff * MOUSE_SENSITIVITY;
}

void Camera::moveForward(float speed)
{
    // TODO: Which vector are you modifying?
    eyePosition[2] -= UNIT_MOVEMENT;
}

void Camera::moveBackward(float speed)
{
    // TODO: Which vector are you modifying?
    eyePosition[2] += UNIT_MOVEMENT;
}

void Camera::moveLeft(float speed)
{
    // TODO: Which vector are you modifying?
    eyePosition[0] -= UNIT_MOVEMENT;
}

void Camera::moveRight(float speed)
{
    // TODO: Which vector are you modifying?
    eyePosition[0] += UNIT_MOVEMENT;
}

void Camera::moveUp(float speed)
{
    // TODO: Which vector are you modifying?
    eyePosition[1] += UNIT_MOVEMENT;
}

void Camera::moveDown(float speed)
{
    // TODO: Which vector are you modifying?
    eyePosition[1] -= UNIT_MOVEMENT;
}

float Camera::getEyeXPosition()
{
    return eyePosition.x;
}

float Camera::getEyeYPosition()
{
    return eyePosition.y;
}

float Camera::getEyeZPosition()
{
    return eyePosition.z;
}

float Camera::getViewXDirection()
{
    return viewDirection.x;
}

float Camera::getViewYDirection()
{
    return viewDirection.y;
}

float Camera::getViewZDirection()
{
    return viewDirection.z;
}

Camera::Camera()
{
    std::cout << "Created a Single Camera!\n";
    // Position us at the origin.
    eyePosition = glm::vec3(0.0f, 0.0f, 10.0f);
    // Looking down along the z-axis initially.
    // Remember, this is negative because we are looking 'into' the scene.
    viewDirection = glm::vec3(0.0f, 0.0f, -1.0f);
    // For now--our upVector always points up along the y-axis
    upVector = glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::mat4 Camera::getWorldToViewmatrix() const
{
    // Think about the second argument and why that is
    // setup as it is.
    return glm::lookAt(eyePosition,
                       eyePosition + viewDirection,
                       upVector);
}
