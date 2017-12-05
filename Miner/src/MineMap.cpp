#include "MineMap.h"
#include <random>
#include <chrono>
#include <algorithm>
#include <iterator>


RandomMineMap::RandomMineMap(size_t size, size_t noMines)
{
	std::mt19937 rnGenerator(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<size_t> distribution(0, size*size);
	for (size_t i = 0; i < noMines; ++i)
	{
		mines.insert(distribution(rnGenerator));
	}
	//std::generate_n(std::inserter(mines, mines.end()), noMines, [&] {return distribution(rnGenerator); });
}


RandomMineMap::~RandomMineMap()
{
}

bool RandomMineMap::isMine(size_t position) const
{
	return mines.find(position) != mines.end();
}
