#ifndef MAZE_H
#define MAZE_H

#include <vector>

enum Direction { north, south, west, east };

class maze {
protected:
    double height;
    double width;
public:
    maze(int h, int w);
    maze();

    virtual ~maze();

    std::vector< std::vector< int > > buildGrid(std::vector< std::vector< int > >& v);

    std::vector< std::pair< int, std::pair< int, int > > > getNeighbors(std::vector< std::vector< int > >& grid, std::vector<std::vector<int>>& v, std::pair< int, int >  &current);
    void markVisited(std::vector< std::vector< int > > &v, std::pair<int, int> current);
    std::pair< int, std::pair< int, int > > pickRandomNeighbor(std::vector< std::pair< int, std::pair< int, int > > >& neighbors, int seed);
    void delNorthWall(std::vector< std::vector< int > > &grid, std::pair<int, int> current);
    void delSouthWall(std::vector< std::vector< int > >& grid, std::pair<int, int> current);
    void delWestWall(std::vector< std::vector< int > >& grid, std::pair<int, int> current);
    void delEastWall(std::vector< std::vector< int > >& grid, std::pair<int, int> current);
};

#endif /* MAZE_H */