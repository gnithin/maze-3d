#ifndef MAZE_GENERATOR_H
#define MAZE_GENERATOR_H
#include <vector>
#include "mazePoint.h"

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
                if (curr.up == -1 || curr.down == -1 || curr.left == -1 || curr.right == -1)
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

    // NOTE: MazePoint(up, down, left, right)
    std::vector<std::vector<MazePoint>>
        mazeMatrix{
            {MazePoint(0, 1, 0, 1), MazePoint(0, 0, 0, 1), MazePoint(0, 0, 0, 0), MazePoint(0, 1, 1, 0)},
            {MazePoint(0, 0, 0, 0), MazePoint(0, 0, 0, 0), MazePoint(0, 0, 0, 0), MazePoint(0, 0, 0, 0)},
            {MazePoint(1, 0, 0, 0), MazePoint(0, 0, 0, 0), MazePoint(0, 0, 0, 0), MazePoint(1, 0, 0, 0)},
            {MazePoint(1, 0, 0, 1), MazePoint(0, 0, 0, 0), MazePoint(0, 0, -1, 0), MazePoint(1, 0, 1, 0)},
        };
};

#endif