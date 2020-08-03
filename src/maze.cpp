#include "maze.h"
#include "mazeGenerator.h"

Maze::Maze()
{
    MazeGenerator *generator = MazeGenerator::instance();
    mazeMatrix = generator->getMazeMatrix();

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

void Maze::update(int screenWidth, int screenHeight)
{
    int matrixSize = mazeMatrix.size();
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
                    j,
                    0.0f,
                    i);
                float rotDirn = 90.0f;
                if (curr.down == 1)
                {
                    rotDirn = -90.0f;
                }
                currWall->getTransform().rotate(glm::radians(rotDirn), 0.0f, 1.0f, 0.0f);
                currWall->update(screenWidth, screenHeight);
            }
            if (curr.right == 1 || curr.left == 1)
            {
                // Horizontal walls
                currWallIndex += 1;
                Object *currWall = objects[currWallIndex];
                currWall->getTransform().loadIdentity();
                currWall->getTransform().translate(
                    j,
                    0.0f,
                    i);

                if (curr.left == 1)
                {
                    currWall->getTransform().rotate(glm::radians(180.f), 0.0f, 1.0f, 0.0f);
                }
                currWall->update(screenWidth, screenHeight);
            }
        }
    }

    // Floor
    float scaleFactor = (matrixSize - 1);

    // Scale the floor according to the size of the matrix
    int floorIndex = numWalls;
    Object *floor = objects[floorIndex];
    floor->getTransform().loadIdentity();
    floor->getTransform().scale(scaleFactor, scaleFactor, scaleFactor);
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

bool Maze::isOnTheWall(float x, float y, float z, float threshold)
{
    // TODO: Add this function
    // First numWall objects are walls
    return false;
}