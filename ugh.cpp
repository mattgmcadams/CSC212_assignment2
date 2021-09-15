
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "maze.h"
//#include "maze.cpp"

using namespace std;

//enum Direction { north, south, West, East };

int main(int argc, char** argv)
{
    int seed = 0;
    int height = 3;
    int width = 3;

    maze m = maze(height, width);

    vector< vector< int > > visited;
    vector< vector< int > > grid = m.buildGrid(visited);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }

    vector< pair< int, pair< int, int > > > neighbors;
    pair<int, int> current = { 0, 0 };
    pair< int, pair< int, int > > neigh;

    vector< pair< int, int > > A;
    std::cout << "created empty dynamic array 'A'" << endl;

    /*create empty dynamic array `A`
        mark cell[0, 0] as visited
        insert cell[0, 0] at the end of `A`
        while `A` is not empty
            `current` < -remove last element from `A`
            `neighbors` < -`current`'s neighbors not visited yet
            if `neighbors` is not empty
                insert `current` at the end of `A`
                `neigh` < -pick a random neighbor from `neighbors`
                remove the wall between `current` and `neigh`
                mark `neigh` as visited
                insert `neigh` at the end of `A`
            endif
        endwhile*/


    m.markVisited(visited, current);
    std::cout << "marked cell [" << current.first << ", " << current.second << "] as visited" << endl;
    A.push_back({ 0, 0 });
    std::cout << "insterted cell [" << current.first << ", " << current.second << "] at the back of 'A'" << endl;
    std::cout << "    A.back() = [" << A.back().first << ", " << A.back().second << "]" << endl;

    std::cout << "while 'A' is not empty: " << endl;
    std::cout << "    A.size() = " << A.size() << endl;
    while (A.size() > 0) {
        current = A.back();
        std::cout << "'current' has been set to the last element of 'A'..." << endl;
        std::cout << "    current = [" << current.first << ", " << current.second << "]" << endl;

        A.pop_back(); //remove last element from A
        std::cout << "...and the last element has been removed from 'A'" << endl;
        std::cout << "    A.size() = " << A.size() << endl;

        std::cout << "'neighbors' will be loaded with neighbors not visited yet" << endl;
        neighbors = m.getNeighbors(grid, visited, current);

        std::cout << "if 'neighbors' is not empty: " << endl;
        std::cout << "    neighbors.size() = " << neighbors.size() << endl;
        if (neighbors.size() > 0) {
            A.push_back({current.first, current.second});
            std::cout << "random neighbor will selected" << endl;
            neigh = m.pickRandomNeighbor(neighbors, seed); //pick random neighbor

            switch (neigh.first) {  //remove wall between current and neighbor
            case 1:
                std::cout << "the north wall of 'current' will be deleted" << endl;
                m.delNorthWall(grid, current);

                break;
            case 2:
                std::cout << "the south wall of 'current' will be deleted" << endl;
                m.delSouthWall(grid, current);

                break;
            case 3:
                std::cout << "the West wall of 'current' will be deleted" << endl;
                m.delWestWall(grid, current);

                break;
            case 4:
                std::cout << "the East wall of 'current' will be deleted" << endl;
                m.delEastWall(grid, current);

                break;


                //mark neighbor as visited
                //std::cout << "current neighbor has been marked as visited" << endl;
                visited[neigh.second.first][neigh.second.second] = 1;

                //INSERT OTHER NEIGHBORS TO A??
                std::cout << "neighbor will be inserted at the end of 'A'" << endl;
                //insert neighbor at the end of A
                A.push_back({ neigh.second.first, neigh.second.second });
                //~~~~~~~~~~~~~~~~~~~~~~~~~~~FIGURE OUT WHY ALL NEIGHBORS AREN'T GETTING HIT!!

                //INSERT REMAINING NEIGHBORS
            }
        }
    }

    std::string out_fname = "maze.txt";

    std::ofstream out_file(out_fname);


    for (unsigned int i = 0; i < grid.size(); i++) {
        for (unsigned int j = 0; j < grid[i].size(); j++) {
            out_file << grid[i][j] << " ";
        }
        out_file << std::endl;
    }


    out_file.close();


    for (unsigned int i = 0; i < visited.size(); i++) {
        for (unsigned int j = 0; j < visited[0].size(); j++) {
            if (!visited[i][j]) {
                std::cout<<"Cell ["<<i<<"]["<<j<<"] has not been visited"<<std::endl;
            }
        }
    }



    return 0;

}
