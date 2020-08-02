#include "maze.h"

#define OBJECTS 4

std::vector<std::vector<MazePoint>> mazeMatrix{
    {MazePoint(0, 1, 0, 1), MazePoint(0, 0, 0, 0)},
    {MazePoint(0, 0, 0, 0), MazePoint(1, 0, 1, 0)},
};

Maze::Maze(int w, int h) : screenWidth(w), screenHeight(h)
{
    // Setup our objects
    for (int i = 0; i < OBJECTS - 1; ++i)
    {
        Object *temp = new Object;
        temp->LoadTexture("brick.ppm");
        objects.push_back(temp);
    }
    // One more object for the floor
    Object *temp = new Object;
    temp->LoadTexture("grass.ppm");
    objects.push_back(temp);
}

std::vector<Object *> Maze::getMazeObjects()
{
    return objects;
}

Maze::~Maze()
{
    for (int i = 0; i < OBJECTS; ++i)
    {
        delete objects[i];
    }
}

void Maze::update()
{
    int matrixSize = mazeMatrix.size();
    float singleSize = 2.0f;

    // // Walls
    // objects[0]->getTransform().loadIdentity();
    // objects[0]->getTransform().translate(0.0f, 0.0f, 0.0f);
    // objects[0]->update(screenWidth, screenHeight);

    // objects[1]->getTransform().loadIdentity();
    // objects[1]->getTransform().translate(1.0f, 0.0f, 0.0f);
    // objects[1]->getTransform().rotate(glm::radians(90.0f), 0.0f, 1.0f, 0.0f);
    // objects[1]->update(screenWidth, screenHeight);

    // objects[2]->getTransform().loadIdentity();
    // objects[2]->getTransform().translate(-1.0f, 0.0f, 0.0f);
    // objects[2]->getTransform().rotate(glm::radians(90.0f), 0.0f, 1.0f, 0.0f);
    // objects[2]->update(screenWidth, screenHeight);

    // Floor
    float scaleFactor = (matrixSize - 1) * singleSize;
    std::cout << "Scale factor - " << scaleFactor << std::endl;

    // Scale the floor according to the size of the matrix
    objects[3]
        ->getTransform()
        .loadIdentity();
    objects[3]->getTransform().translate(0.0f, -1.0f, 0.0f);
    objects[3]->getTransform().scale(scaleFactor, scaleFactor, scaleFactor);
    objects[3]->getTransform().rotate(glm::radians(90.0f), 1.0f, 0.0f, 0.0f);
    objects[3]->update(screenWidth, screenHeight);
}

void Maze::render()
{
    // Render all of our objects in a simple loop
    for (int i = 0; i < OBJECTS; ++i)
    {
        objects[i]->render();
    }
}