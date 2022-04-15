#include <iostream>
#include <stack>
#include <utility>
#include <vector>

struct maze {
	int width{ 0 };
	int height{ 0 };
	int* mazeArr{nullptr};
	int numvisted {0};

	std::stack<std::pair<int, int>> stack;

	enum states {
		north = 0x01,
		south = 0x02,
		east = 0x04,
		west = 0x08,
		visted = 0x10
	};

	void createMaze() {
		height = 5;
		width = 5;
		mazeArr = new int[height * width];
	}

	void createMaze(int x, int y) {

		height = x;
		width = y;
		mazeArr = new int[height * width];
	}

	void init() {
		stack.push(std::make_pair(0, 0));
		mazeArr[0] = visted;
		numvisted = 1;
	}

	void start() {

		// Little lambda function to calculate index in a readable way
		auto offset = [&](int x, int y)
		{
			return (stack.top().second + y) * width + (stack.top().first + x);
			// ((0+0) * 4) + 1 = 1;
		};

		// Do Maze Algorithm
		if (numvisted < width * height)
		{
			// Create a set of unvisted neighbours
			std::vector<int> neighbours;

			// North neighbour
			if (stack.top().second > 0 && (mazeArr[offset(0, -1)] & visted) == 0)
				neighbours.push_back(0);
			// East neighbour
			if (stack.top().first < width - 1 && (mazeArr[offset(1, 0)] & visted) == 0)
				neighbours.push_back(1);
			// South neighbour
			if (stack.top().second < height - 1 && (mazeArr[offset(0, 1)] & visted) == 0)
				neighbours.push_back(2);
			// West neighbour
			if (stack.top().first > 0 && (mazeArr[offset(-1, 0)] & visted) == 0)
				neighbours.push_back(3);

			// Are there any neighbours available?
			if (!neighbours.empty())
			{
				// Choose one available neighbour at random
				int next_cell_dir = neighbours[rand() % neighbours.size()];

				// Create a path between the neighbour and the current cell
				switch (next_cell_dir)
				{
				case 0: // North
					mazeArr[offset(0, -1)] |= visted | south;
					mazeArr[offset(0, 0)] |= north;
					stack.push(std::make_pair((stack.top().first + 0), (stack.top().second - 1)));
					break;

				case 1: // East
					mazeArr[offset(+1, 0)] |= visted | west;
					mazeArr[offset(0, 0)] |= east;
					stack.push(std::make_pair((stack.top().first + 1), (stack.top().second + 0)));
					break;

				case 2: // South
					mazeArr[offset(0, +1)] |= visted | north;
					mazeArr[offset(0, 0)] |= south;
					stack.push(std::make_pair((stack.top().first + 0), (stack.top().second + 1)));
					break;

				case 3: // West
					mazeArr[offset(-1, 0)] |= visted | east;
					mazeArr[offset(0, 0)] |= west;
					stack.push(std::make_pair((stack.top().first - 1), (stack.top().second + 0)));
					break;

				}

				numvisted++;
			}
			else
			{
				// No available neighbours so backtrack!
				stack.pop();
			}

			start();

		}
	}


};


int main() {
	maze game;
	game.createMaze(5,5);
	game.init();
	game.start();
	std::cout << game.numvisted;
	return 0;
}