#ifndef MAZE_POINT_H
#define MAZE_POINT_H

class MazePoint
{
public:
    MazePoint(int u, int d, int l, int r) : up(u), down(d), left(l), right(r){};
    int up, down, left, right;
};

#endif