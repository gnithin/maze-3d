#include "maze.h"

#define UNIT_DISTANCE 2.0f

std::vector<std::vector<MazePoint>> mazeMatrix{
    {MazePoint(0, 1, 0, 1), MazePoint(0, 0, 0, 0)},
    {MazePoint(0, 0, 0, 0), MazePoint(1, 0, 1, 0)},
};

Maze::Maze(int w, int h) : screenWidth(w), screenHeight(h)
{
    // Get the number of walls;
    numWalls = 0;
    for (int i = 0; i < mazeMatrix.size(); i++)
    {
        for (int j = 0; j < mazeMatrix.size(); j++)
        {
            MazePoint mazePoint = mazeMatrix[i][j];
            if (mazePoint.up == 1)
            {
                numWalls += 1;
            }
            if (mazePoint.down == 1)
            {
                numWalls += 1;
            }
            if (mazePoint.left == 1)
            {
                numWalls += 1;
            }
            if (mazePoint.right == 1)
            {
                numWalls += 1;
            }
        }
    }

    // Setup our objects
    for (int i = 0; i < numWalls; ++i)
    {
        Object *wall = new Object;
        wall->LoadTexture("brick.ppm");
        objects.push_back(wall);
    }
    // One more object for the floor
    Object *floor = new Object;
    floor->LoadTexture("grass.ppm");
    objects.push_back(floor);
}

std::vector<Object *> Maze::getMazeObjects()
{
    return objects;
}

Maze::~Maze()
{
    for (int i = 0; i < numWalls; ++i)
    {
        delete objects[i];
    }
}

void Maze::update()
{
    int matrixSize = mazeMatrix.size();
    float singleSize = UNIT_DISTANCE;

    int currWallIndex = -1;
    for (int i = 0; i < mazeMatrix.size(); i += 1)
    {
        for (int j = 0; j < mazeMatrix.size(); j += 1)
        {
            MazePoint curr = mazeMatrix[i][j];
            if (curr.up == 1 || curr.down == 1)
            {
                // Vertical walls
                currWallIndex += 1;
                Object *currWall = objects[currWallIndex];
                currWall->getTransform().loadIdentity();
                currWall->getTransform().translate(
                    getXIdentityTranslationForIndex(j),
                    0.0f,
                    getXIdentityTranslationForIndex(i));
                currWall->getTransform().rotate(glm::radians(90.0f), 0.0f, 1.0f, 0.0f);
                currWall->update(screenWidth, screenHeight);
            }
            if (curr.left == 1 || curr.right == 1)
            {
                // Horizontal walls
                currWallIndex += 1;
                Object *currWall = objects[currWallIndex];
                currWall->getTransform().loadIdentity();
                currWall->getTransform().translate(
                    getXIdentityTranslationForIndex(j),
                    0.0f,
                    getXIdentityTranslationForIndex(i));
                currWall->update(screenWidth, screenHeight);
            }
        }
    }
    // Walls
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

    // Scale the floor according to the size of the matrix
    int floorIndex = numWalls;
    Object *floor = objects[floorIndex];
    floor->getTransform().loadIdentity();
    floor->getTransform().translate(0.0f, -1.0f, 0.0f);
    // floor->getTransform().scale(scaleFactor, scaleFactor, scaleFactor);
    floor->getTransform().rotate(glm::radians(90.0f), 1.0f, 0.0f, 0.0f);
    floor->update(screenWidth, screenHeight);
}

void Maze::render()
{
    // Render all of our objects in a simple loop
    for (int i = 0; i < objects.size(); i += 1)
    {
        objects[i]->render();
    }
}

float Maze::getXIdentityTranslationForIndex(int c)
{
    float res = ((((float)c) / (mazeMatrix.size() - 1)) * 2.0f) - 1.0f;
    return res;
}