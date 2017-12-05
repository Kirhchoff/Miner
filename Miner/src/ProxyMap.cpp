#include "ProxyMap.h"
#include "IMineMap.h"



Labels::Labels(std::shared_ptr<IMineMap> mines, size_t size) : mines(mines), size(size), labels(size*size, 0)
{
	populate();
}


Labels::~Labels()
{
}

bool Labels::isUncovered(size_t boxId) const
{
	return std::find(uncovered.cbegin(), uncovered.cend(), boxId) != uncovered.cend();
}

std::string Labels::uncover(size_t boxId)
{
	uncovered.insert(boxId);
	if (mines->isMine(boxId))
	{
		return "X";
	}
	return std::to_string(labels[boxId]);
}

void Labels::populate()
{
	for (size_t pos = 0; pos < size*size; pos++)
	{
		if (mines->isMine(pos))
		{
			updateTipsAround(pos);
		}
	}
}

void Labels::updateTipsAround(size_t pos)
{
	if (pos >= size)
	{
		update3Row(pos - size);
	}
	update3Row(pos);
	if (pos < size*size - size)
	{
		update3Row(pos + size);
	}
}

void Labels::update3Row(size_t centerPos)
{
	if (centerPos % size > 0)
	{
		labels[centerPos - 1]++;
	}
	labels[centerPos]++;
	if (centerPos%size < size - 1)
	{
		labels[centerPos + 1]++;
	}
}
