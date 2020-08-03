#ifndef MAZE_H
#define MAZE_H

#include <vector>

#include "Object.h"
#include "mazePoint.h"

// NOTE: The WALL_THRESHOLD and the UNIT_MOVEMENT in the camera are linked.
// If there is trouble with hitting the walls, play around with these parameters.
// Usually the WALL_THRESHOLD must be a bit higher that the UNIT_MOVEMENT (else
// the camera moves over the threshold and walks between walls)
#define WALL_THRESHOLD 0.12f

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
    bool isOnTheWall(float x, float y, float z, float threshold = WALL_THRESHOLD);
    ~Maze();

private:
    Maze();
    int numWalls;
    std::vector<std::vector<MazePoint>> mazeMatrix;

    // All the maze objects
    std::vector<Object *> objects;
};

#endif