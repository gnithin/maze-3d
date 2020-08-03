#include "Camera.h"

#include "glm/gtx/transform.hpp"
#include "mazeGenerator.h"

#include <iostream>

const float UNIT_MOVEMENT = 0.10;
const float MOUSE_SENSITIVITY = 0.003;

Camera &Camera::instance()
{
    static Camera *instance = new Camera();
    return *instance;
}

void Camera::mouseLook(int mouseX, int mouseY)
{
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
    float newPosition = eyePosition[2] - UNIT_MOVEMENT;
    if (!maze->isOnTheWall(eyePosition[0], eyePosition[1], newPosition))
    {
        eyePosition[2] = newPosition;
    }
}

void Camera::moveBackward(float speed)
{
    float newPosition = eyePosition[2] + UNIT_MOVEMENT;
    if (!maze->isOnTheWall(eyePosition[0], eyePosition[1], newPosition))
    {
        eyePosition[2] = newPosition;
    }
}

void Camera::moveLeft(float speed)
{
    float newPosition = eyePosition[0] - UNIT_MOVEMENT;
    if (!maze->isOnTheWall(newPosition, eyePosition[1], eyePosition[2]))
    {
        eyePosition[0] = newPosition;
    }
}

void Camera::moveRight(float speed)
{
    float newPosition = eyePosition[0] + UNIT_MOVEMENT;
    if (!maze->isOnTheWall(newPosition, eyePosition[1], eyePosition[2]))
    {
        eyePosition[0] = newPosition;
    }
}

void Camera::moveUp(float speed)
{
    eyePosition[1] += UNIT_MOVEMENT;
}

void Camera::moveDown(float speed)
{
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
    // Position us at the origin.
    MazeGenerator *generator = MazeGenerator::instance();
    int i, j;
    generator->getStartingIndex(&i, &j);

    float delta = 0.5f;
    eyePosition = glm::vec3(
        (j * 1.0f) - delta,
        0.5f,
        (i * 1.0f) + delta);
    // Looking down along the z-axis initially.
    // Remember, this is negative because we are looking 'into' the scene.
    viewDirection = glm::vec3(0.0f, 0.0f, -1.0f);
    // For now--our upVector always points up along the y-axis
    upVector = glm::vec3(0.0f, 1.0f, 0.0f);
    maze = Maze::instance();
}

glm::mat4 Camera::getWorldToViewmatrix() const
{
    // Think about the second argument and why that is
    // setup as it is.
    return glm::lookAt(eyePosition,
                       eyePosition + viewDirection,
                       upVector);
}
