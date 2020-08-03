#ifndef MAZE_H
#define MAZE_H

#include <vector>

#include "Object.h"
#include "mazePoint.h"

class Maze
{
public:
    Maze();
    std::vector<Object *> getMazeObjects();
    void update(int screenWidth, int screenHeight);
    void render();
    void getStartingIndex(int *r, int *c);
    bool isOnTheWall(float x, float y, float z, float threshold = 0.10f);
    ~Maze();

private:
    int numWalls;
    std::vector<std::vector<MazePoint>> mazeMatrix;

    // All the maze objects
    std::vector<Object *> objects;
};

#endif