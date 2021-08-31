/* Your code here! */
#pragma once
#include <vector>
#include <utility>
#include "cs225/PNG.h"
#include "dsets.h"

using namespace cs225;

class SquareMaze{
    public:
    SquareMaze();
    void makeMaze (int width, int height);
    bool canTravel (int x, int y, int dir) const;
    void setWall (int x, int y, int dir, bool exists);
    std::vector<int> solveMaze();
    PNG *drawMaze() const;
    PNG *drawMazeWithSolution();

    private:
    int _height;
    int _width;
    std::vector<std::vector<std::pair<bool, bool>>> walls;
};
