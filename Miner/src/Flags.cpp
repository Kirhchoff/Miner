#include "Flags.h"

Flags::Flags()
{
}

void Flags::toggleFlag(size_t boxId)
{
	auto found = std::find(flags.begin(), flags.end(), boxId);
	if (found == flags.end())
	{
		flags.push_front(boxId);
	}
	else
	{
		flags.erase(found);
	}
}

bool Flags::isFlagged(size_t boxId) const
{
	return std::find(flags.cbegin(), flags.cend(), boxId) != flags.cend();
}
