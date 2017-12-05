#pragma once

#include <list>

class Flags
{
public:
	Flags();

	void toggleFlag(size_t boxId);
	bool isFlagged(size_t boxId) const;


private:
	std::list<size_t> flags;
};