#ifndef MAZE_H
#define MAZE_H

#include <vector>

#include "Object.h"
#include "mazePoint.h"

class Maze
{
public:
    Maze(int w, int h);
    std::vector<Object *> getMazeObjects();
    void update();
    void render();
    void getStartingIndex(int *r, int *c);
    ~Maze();

private:
    // Screen dimension constants
    int screenHeight;
    int screenWidth;
    int numWalls;
    std::vector<std::vector<MazePoint>> mazeMatrix;

    // All the maze objects
    std::vector<Object *> objects;

    float getXIdentityTranslationForIndex(int c);
    float getHalfUnit();
};

#endif