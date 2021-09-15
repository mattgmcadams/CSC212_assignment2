
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "maze.h"
//#include "maze.cpp"

using namespace std;

int main(int argc, char** argv)
{
    int seed = std::stoi(argv[1]);
    int height = std::stoi(argv[2]);
    int width = std::stoi(argv[3]);

    int countWhile = 0, countIf = 0;
    std::srand(seed);

    maze m = maze(height, width);

    vector< vector< int > > visited;
    vector< vector< int > > grid = m.buildGrid(visited);

    vector< pair< int, pair< int, int > > > neighbors;
    pair<int, int> current = { 0, 0 };
    pair< int, pair< int, int > > neigh;

    vector< pair< int, int > > A;

//create empty dynamic array `A`








        //remove the wall between `current` and `neigh`
        //mark `neigh` as visited
        //insert `neigh` at the end of `A`
    //endif
//endwhile

    m.markVisited(visited, current);    //mark cell [0,0] as visited
    A.push_back({ 0, 0 });              //insert cell [0,0] at the end of `A`
    while (A.size() > 0) {              //while `A` is not empty

        current = A.back();
        A.pop_back();                   //`current` <- remove last element from `A`

        neighbors = m.getNeighbors(grid, visited, current);
                                        //`neighbors` <- `current`'s neighbors not visited yet

        if (neighbors.size() > 0) {     //if `neighbors` is not empty

            A.push_back({ current.first, current.second });
                                        //insert `current` at the end of `A`
            neigh = m.pickRandomNeighbor(neighbors, seed);
                                        //`neigh` <- pick a random neighbor from `neighbors`

            switch (neigh.first) {  //remove wall between current and neighbor
            case 1:
                m.delNorthWall(grid, current);
                break;
            case 2:
                m.delSouthWall(grid, current);
                break;
            case 3:
                m.delEastWall(grid, current);
                break;
            case 4:
                m.delWestWall(grid, current);
                break;
            }

            visited[neigh.second.first][neigh.second.second] = 1;

            A.push_back({ neigh.second.first, neigh.second.second });

        }
        countIf = 0;
    }

    std::string out_fname = argv[4];

    std::ofstream out_file(out_fname);

    if(height==1&&width==1){
        out_file<<3;
    }
    else {
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                out_file << grid[i][j] << " ";
            }
            out_file << std::endl;
        }
    }

    out_file.close();



    return 0;

}
