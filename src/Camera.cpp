#include "Camera.h"

#include "glm/gtx/transform.hpp"
#include "mazeGenerator.h"
#include "keyControlsManager.h"

#include <iostream>

const float UNIT_MOVEMENT = 0.10;
const float MOUSE_SENSITIVITY = 1.75f;
const float MOUSE_H_THRESHOLD = 0.1;
const float MOUSE_V_THRESHOLD = 0.5;

const float REGULAR_HEIGHT = 0.5f;
const float PEEK_HEIGHT = 2.5f;

const int VERTICAL_CHANGE_LIMIT = 15;

Camera &Camera::instance()
{
    static Camera *instance = new Camera();
    return *instance;
}

void Camera::mouseLook(int mouseX, int mouseY, int mouseXrel, int mouseYrel)
{
    if (oldMousePosition.x == 0 && oldMousePosition.y == 0)
    {
        oldMousePosition.x = mouseX;
        oldMousePosition.y = mouseY;
        return;
    }

    if (abs(mouseXrel) > MOUSE_H_THRESHOLD)
    {
        oldMousePosition.x = mouseX;
        if (mouseXrel > 0)
        {
            lookRight(MOUSE_SENSITIVITY);
        }
        else if (mouseXrel < 0)
        {
            lookLeft(MOUSE_SENSITIVITY);
        }
    }
}

void Camera::moveOnXZ(float newPositionX, float newPositionZ)
{
    if (!maze->isOnTheWall(newPositionX, eyePosition[1], newPositionZ))
    {
        eyePosition[0] = newPositionX;
        eyePosition[2] = newPositionZ;
    }
}

void Camera::moveForward(float speed)
{
    //float newPosition = eyePosition[2] - UNIT_MOVEMENT;
    float newPositionX = eyePosition[0] + speed * UNIT_MOVEMENT * cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    float newPositionZ = eyePosition[2] + speed * UNIT_MOVEMENT * sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    moveOnXZ(newPositionX, newPositionZ);
}

void Camera::moveBackward(float speed)
{
    //float newPosition = eyePosition[2] + UNIT_MOVEMENT;
    float newPositionX = eyePosition[0] - speed * UNIT_MOVEMENT * cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    float newPositionZ = eyePosition[2] - speed * UNIT_MOVEMENT * sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    moveOnXZ(newPositionX, newPositionZ);
}

void Camera::moveLeft(float speed)
{
    //float newPosition = eyePosition[2] + UNIT_MOVEMENT;
    float newPositionX = eyePosition[0] + speed * UNIT_MOVEMENT * sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    float newPositionZ = eyePosition[2] - speed * UNIT_MOVEMENT * cos(glm::radians(yaw)) * cos(glm::radians(pitch));

    moveOnXZ(newPositionX, newPositionZ);
}

void Camera::moveRight(float speed)
{
    //float newPosition = eyePosition[2] + UNIT_MOVEMENT;
    float newPositionX = eyePosition[0] - speed * UNIT_MOVEMENT * sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    float newPositionZ = eyePosition[2] + speed * UNIT_MOVEMENT * cos(glm::radians(yaw)) * cos(glm::radians(pitch));

    moveOnXZ(newPositionX, newPositionZ);
}

void Camera::moveUp(float speed)
{
    eyePosition[1] += UNIT_MOVEMENT;
}

void Camera::moveDown(float speed)
{
    eyePosition[1] -= UNIT_MOVEMENT;
}

void Camera::togglePeek()
{
    float height;

    if ((KeyControlsManager::instance())->isPeekMode)
    {
        height = PEEK_HEIGHT;
        for (int i = 0; i <= VERTICAL_CHANGE_LIMIT; i += 1)
        {
            lookUp(1.0f);
        }
    }
    else
    {
        height = REGULAR_HEIGHT;
        for (int i = 0; i < VERTICAL_CHANGE_LIMIT; i += 1)
        {
            lookDown(1.0f);
        }
    }
    eyePosition[1] = height;
}

void Camera::setLookDirection()
{
    viewDirection.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    viewDirection.y = sin(glm::radians(pitch));
    viewDirection.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
}

void Camera::lookLeft(float speed)
{

    float xdiff = -2.0f * speed;
    yaw += xdiff;
    setLookDirection();
}

void Camera::lookRight(float speed)
{

    float xdiff = 2.0f * speed;
    yaw += xdiff;
    setLookDirection();
}

void Camera::lookDown(float speed)
{

    float ydiff = 0.5f * speed;
    pitch += ydiff;

    if (pitch > 89.0f)
    {
        pitch = 89.0f;
    }
    else if (pitch < -89.0f)
    {
        pitch = -89.0f;
    }

    setLookDirection();
}

void Camera::lookUp(float speed)
{

    float ydiff = -0.5f * speed;

    pitch += ydiff;

    if (pitch > 89.0f)
    {
        pitch = 89.0f;
    }
    else if (pitch < -89.0f)
    {
        pitch = -89.0f;
    }

    setLookDirection();
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
    float height = REGULAR_HEIGHT;
    if ((KeyControlsManager::instance())->isPeekMode)
    {
        height = PEEK_HEIGHT;
    }

    eyePosition = glm::vec3(
        (j * 1.0f) - delta,
        height,
        (i * 1.0f));
    // Looking down along the z-axis initially.
    // Remember, this is negative because we are looking 'into' the scene.
    viewDirection = glm::vec3(0.0f, 0.0f, -1.0f);
    // For now--our upVector always points up along the y-axis
    upVector = glm::vec3(0.0f, 1.0f, 0.0f);

    //mouse view:
    yaw = -90.0f;
    pitch = 0.0f;

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
