#pragma once

#include "IMineMap.h"
#include <set>

class RandomMineMap : public IMineMap
{
public:
	RandomMineMap(size_t size, size_t noMines);
	~RandomMineMap();

	bool isMine(size_t position) const override;
private:
	std::set<size_t> mines;
};

