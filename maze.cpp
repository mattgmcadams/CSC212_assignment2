#include "maze.h"
#include <iostream>
#include <vector>


maze::maze(int h=5, int w=5) {
	this->height = h;
	this->width = w;
}


std::vector< std::vector< int > > maze::buildGrid(std::vector< std::vector<int> >& v) {
	std::cout << "Building grid..." << std::endl;

	std::vector< std::vector< int > > grid;
	std::vector< int > row;
	std::vector< int > vrow;


	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (i==0 && j==0) {
				row.push_back(7);
				vrow.push_back(false);
			}
			else if (i == height - 1 && j == width - 1) {
				row.push_back(11);
				vrow.push_back(false);
			}
			else {
				row.push_back(15);
				vrow.push_back(false);
			}
		}
		grid.push_back(row);
		v.push_back(vrow);
		row.clear();
		vrow.clear();
	}
	std::cout << "    Grid built" << std::endl;
	return grid;
}

std::vector< std::pair< int, std::pair< int, int > > > maze::getNeighbors(std::vector< std::vector< int > >& grid, std::vector<std::vector<int>>& v, std::pair< int, int >& current) {

	int x = current.first;
	int y = current.second;

	std::cout << "Getting neighbors..." << std::endl;
	std::vector< std::pair< int, std::pair< int, int > > > neighbors;


	std::vector< std::pair< int, int > > neigh = { { x - 1, y }, { x + 1, y },
		{ x, y + 1 }, { x, y - 1 } };

	int direction = 1;
	std::cout << "Where 1:north, 2:south, 3:west, 4:east " << std::endl;
	for (unsigned int i = 0; i < neigh.size(); i++) {
		if (neigh[i].first >= 0 && neigh[i].second >=0) {
			if (neigh[i].first < grid.size() && neigh[i].second < grid[0].size()) {
				if (!v[neigh[i].first][neigh[i].second]) {
					neighbors.push_back({ direction, neigh[i] });
					std::cout << "Direction: " << direction << " has been added to 'neighbors'" << std::endl;
				}
			}
		}
		direction++;
	}


	return neighbors;

}

void maze::markVisited(std::vector< std::vector< int > >& v, std::pair<int, int> current) {
	std::cout << "Marking cell [" << current.first << ", " << current.second << "] as VISITED..." << std::endl;
	v[current.first][current.second] = 1;
}

std::pair< int, std::pair< int, int > > maze::pickRandomNeighbor(std::vector< std::pair< int, std::pair< int, int > > >& neighbors, int seed) {
	std::cout << "Picking random neighbor..." << std::endl;

	//std::srand(seed);

	std::pair< int, std::pair< int, int > > neigh;

	int idx = std::rand() / ((RAND_MAX + 1u) / neighbors.size());

	neigh = neighbors[idx];

	std::cout << "Picked neighbor: " << idx << std::endl;



	return neigh;
}

		//N S E W
		//1 0 0 0 = -8
		//0 1 0 0 = -4
void maze::delNorthWall(std::vector< std::vector< int > >& grid, std::pair<int, int> current) {

	grid[current.first][current.second] -= 8;
	grid[current.first-1][current.second] -= 4;

	std::cout << "The north wall of 'current' hass been deleted" << std::endl;

}

		//0 1 0 0 = -4
		//1 0 0 0 = -8
void maze::delSouthWall(std::vector< std::vector< int > >& grid, std::pair<int, int> current) {
	grid[current.first][current.second] -= 4;
	grid[current.first + 1][current.second] -= 8;

	std::cout << "The south wall of 'current' hass been deleted" << std::endl;
}

		//0 0 1 0 = -2
		//0 0 0 1 = -1
void maze::delWestWall(std::vector< std::vector< int > >& grid, std::pair<int, int> current) {
	grid[current.first][current.second] -= 1;
	grid[current.first][current.second-1] -= 2;

	std::cout << "The west wall of 'current' hass been deleted" << std::endl;
}


		//0 0 0 1 = -1
		//0 0 1 0 = -2
void maze::delEastWall(std::vector< std::vector< int > >& grid, std::pair<int, int> current) {
	grid[current.first][current.second] -= 2;
	grid[current.first][current.second + 1] -= 1;

	std::cout << "The east wall of 'current' hass been deleted" << std::endl;
}


maze::~maze() = default;
