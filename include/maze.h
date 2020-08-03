#ifndef MAZE_H
#define MAZE_H

#include <vector>

#include "Object.h"
#include "mazePoint.h"

class Maze
{
public:
    static Maze *instance()
    {
        static Maze *mazeInstance = new Maze();
        return mazeInstance;
    }

    std::vector<Object *> getMazeObjects();
    void update(int screenWidth, int screenHeight);
    void render();
    void getStartingIndex(int *r, int *c);
    bool isOnTheWall(float x, float y, float z, float threshold = 0.12f);
    ~Maze();

private:
    Maze();
    int numWalls;
    std::vector<std::vector<MazePoint>> mazeMatrix;

    // All the maze objects
    std::vector<Object *> objects;
};

#endif