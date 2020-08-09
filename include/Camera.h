/** @file Camera.h
 *  @brief Sets up an OpenGL camera.
 *  
 *  Sets up an OpenGL Camera. The camera is what
 *  sets up our 'view' matrix.
 *
 *  @author Mike
 *  @bug No known bugs.
 */

#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"
#include "maze.h"

class Camera
{
public:
    // Singleton pattern for having one single camera.
    static Camera &instance();

    // Constructor
    Camera();
    // Return a 'view' matrix with our
    // camera transformation applied.
    glm::mat4 getWorldToViewmatrix() const;
    // Move the camera around
    void mouseLook(int mouseX, int mouseY, int mouseXrel, int mouseYrel);

    void moveForward(float speed);
    void moveBackward(float speed);
    void moveLeft(float speed);
    void moveRight(float speed);

    void moveUp(float speed);
    void moveDown(float speed);

    //mouse look:
    void lookLeft(float speed);
    void lookRight(float speed);
    void lookUp(float speed);
    void lookDown(float speed);

    // Returns the 'eye' position which
    // is where the camera is.
    float getEyeXPosition();
    float getEyeYPosition();
    float getEyeZPosition();

    float getViewXDirection();
    float getViewYDirection();
    float getViewZDirection();

    void togglePeek();

    void update();

private:
    // Track the old mouse position
    glm::vec2 oldMousePosition;
    // Where is our camera positioned
    glm::vec3 eyePosition;
    // What direction is the camera looking
    glm::vec3 viewDirection;
    // Which direction is 'up' in our world
    // Generally this is constant, but if you wanted
    // to 'rock' or 'rattle' the camera you might play
    // with modifying this value.
    glm::vec3 upVector;

    // mouse view:
    void setLookDirection();
    void moveOnXZ(float newPositionX, float newPositionZ);
    float yaw;
    float pitch;

    Maze *maze;
};

#endif
