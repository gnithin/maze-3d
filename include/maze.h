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
    ~Maze();

private:
    // Screen dimension constants
    int screenHeight;
    int screenWidth;

    // All the maze objects
    std::vector<Object *> objects;
};

#endif