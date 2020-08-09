#ifndef MAZE_GENERATOR_H
#define MAZE_GENERATOR_H
#include <vector>
#include "mazePoint.h"

#define STARTING_NODE_MARKER -1
#define ENDING_NODE_MARKER -2

class MazeGenerator
{
public:
    static MazeGenerator *instance()
    {
        static MazeGenerator *instance = new MazeGenerator();
        return instance;
    }

    std::vector<std::vector<MazePoint>> getMazeMatrix()
    {
        return mazeMatrix;
    }

    void getStartingIndex(int *r, int *c)
    {
        // Starting maze point is the maze-point which contains -1 for any entry
        for (int i = 0; i < mazeMatrix.size(); i++)
        {
            for (int j = 0; j < mazeMatrix.size(); j++)
            {
                MazePoint curr = mazeMatrix[i][j];
                if (
                    curr.up == STARTING_NODE_MARKER ||
                    curr.down == STARTING_NODE_MARKER ||
                    curr.left == STARTING_NODE_MARKER ||
                    curr.right == STARTING_NODE_MARKER)
                {
                    *r = i;
                    *c = j;
                    return;
                }
            }
        }

        *r = mazeMatrix.size() - 1;
        *c = mazeMatrix.size() - 1;
    }

    void getEndingIndex(int *r, int *c)
    {
        // Starting maze point is the maze-point which contains -1 for any entry
        for (int i = 0; i < mazeMatrix.size(); i++)
        {
            for (int j = 0; j < mazeMatrix.size(); j++)
            {
                MazePoint curr = mazeMatrix[i][j];
                if (
                    curr.up == ENDING_NODE_MARKER ||
                    curr.down == ENDING_NODE_MARKER ||
                    curr.left == ENDING_NODE_MARKER ||
                    curr.right == ENDING_NODE_MARKER)
                {
                    *r = i;
                    *c = j;
                    return;
                }
            }
        }

        *r = mazeMatrix.size() - 1;
        *c = mazeMatrix.size() - 1;
    }

private:
    MazeGenerator(){
        // Prevent anyone from calling this
    };

#ifdef MAZE_DEBUG_MODE
    // NOTE: MazePoint(up, down, left, right)
    std::vector<std::vector<MazePoint>>
        mazeMatrix{
            {MazePoint(0, 1, 0, 1), MazePoint(0, 0, 0, 1), MazePoint(0, 0, ENDING_NODE_MARKER, 0), MazePoint(0, 0, 0, 0), MazePoint(0, 1, 1, 0)},
            {MazePoint(0, 0, 0, 0), MazePoint(0, 0, 0, 0), MazePoint(0, 0, 1, 0), MazePoint(0, 0, 1, 0), MazePoint(0, 0, 0, 0)},
            {MazePoint(1, 0, 0, 0), MazePoint(0, 1, 0, 0), MazePoint(0, 0, 1, 0), MazePoint(1, 0, 0, 0), MazePoint(1, 0, 0, 0)},
            {MazePoint(1, 0, 0, 0), MazePoint(0, 0, 1, 0), MazePoint(1, 0, 0, 0), MazePoint(1, 0, 0, 0), MazePoint(1, 0, 0, 0)},
            {MazePoint(1, 0, 0, 1), MazePoint(0, 0, 1, 0), MazePoint(1, 0, 1, 0), MazePoint(1, 0, STARTING_NODE_MARKER, 0), MazePoint(1, 0, 1, 0)},
        };

#else
    // NOTE: MazePoint(up, down, left, right)
    std::vector<std::vector<MazePoint>>
        mazeMatrix{
            //          1                       2                       3                   4                       5                           6                  7                    8                      9                    10
            {MazePoint(0, 0, 0, 0), MazePoint(0, 0, 1, 0), MazePoint(0, 0, 1, 0), MazePoint(0, 0, 1, 0), MazePoint(0, 0, 1, 0), MazePoint(0, 0, 1, 0), MazePoint(0, 0, 1, 0), MazePoint(0, 0, 1, 0), MazePoint(0, 0, ENDING_NODE_MARKER, 0), MazePoint(0, 1, 1, 0)},
            {MazePoint(1, 0, 0, 1), MazePoint(0, 0, 0, 1), MazePoint(0, 0, 0, 0), MazePoint(0, 0, 0, 1), MazePoint(1, 0, 0, 1), MazePoint(0, 0, 0, 0), MazePoint(0, 0, 0, 0), MazePoint(0, 0, 1, 0), MazePoint(0, 0, 0, 0), MazePoint(0, 1, 0, 0)},
            {MazePoint(1, 0, 0, 1), MazePoint(0, 0, 0, 1), MazePoint(0, 0, 0, 1), MazePoint(0, 0, 0, 0), MazePoint(0, 0, 0, 1), MazePoint(0, 0, 0, 1), MazePoint(0, 0, 0, 1), MazePoint(1, 0, 0, 0), MazePoint(1, 0, 0, 0), MazePoint(0, 1, 0, 0)},
            {MazePoint(1, 0, 0, 0), MazePoint(0, 0, 0, 0), MazePoint(0, 0, 0, 1), MazePoint(0, 0, 0, 1), MazePoint(1, 0, 0, 0), MazePoint(0, 0, 0, 1), MazePoint(0, 0, 0, 1), MazePoint(0, 0, 0, 1), MazePoint(1, 0, 0, 0), MazePoint(0, 1, 0, 0)},
            {MazePoint(1, 0, 0, 1), MazePoint(0, 0, 0, 0), MazePoint(1, 0, 0, 0), MazePoint(0, 0, 0, 1), MazePoint(0, 0, 0, 1), MazePoint(0, 0, 0, 1), MazePoint(1, 0, 0, 0), MazePoint(0, 0, 0, 1), MazePoint(1, 0, 0, 0), MazePoint(0, 1, 0, 0)},
            {MazePoint(1, 0, 0, 0), MazePoint(0, 0, 0, 0), MazePoint(1, 0, 0, 0), MazePoint(1, 0, 0, 0), MazePoint(0, 0, 1, 0), MazePoint(0, 0, 1, 0), MazePoint(0, 0, 0, 1), MazePoint(0, 0, 0, 1), MazePoint(0, 0, 0, 1), MazePoint(0, 1, 0, 0)},
            {MazePoint(1, 0, 0, 0), MazePoint(1, 0, 0, 0), MazePoint(1, 0, 1, 0), MazePoint(0, 0, 1, 0), MazePoint(0, 0, 1, 0), MazePoint(0, 0, 0, 1), MazePoint(0, 0, 0, 0), MazePoint(0, 0, 0, 0), MazePoint(0, 0, 1, 0), MazePoint(0, 1, 1, 0)},
            {MazePoint(1, 0, 0, 1), MazePoint(0, 0, 0, 1), MazePoint(0, 0, 0, 1), MazePoint(0, 0, 0, 0), MazePoint(1, 0, 0, 0), MazePoint(1, 0, 0, 1), MazePoint(0, 0, 0, 1), MazePoint(0, 0, 0, 0), MazePoint(0, 0, 0, 0), MazePoint(0, 1, 1, 0)},
            {MazePoint(1, 0, 0, 1), MazePoint(0, 0, 0, 1), MazePoint(0, 0, 0, 0), MazePoint(0, 0, 0, 0), MazePoint(1, 0, 1, 0), MazePoint(0, 0, 0, 0), MazePoint(0, 0, 1, 1), MazePoint(0, 0, 0, 1), MazePoint(0, 0, 0, 0), MazePoint(0, 1, 0, 0)},
            {MazePoint(1, 0, 0, 0), MazePoint(0, 0, 1, 0), MazePoint(0, 0, 1, 0), MazePoint(STARTING_NODE_MARKER, 0, 0, 0), MazePoint(0, 0, 1, 0), MazePoint(0, 0, 1, 0), MazePoint(1, 0, 1, 0), MazePoint(0, 0, 1, 0), MazePoint(0, 0, 1, 0), MazePoint(0, 0, 1, 0)},
        };

#endif
};

#endif