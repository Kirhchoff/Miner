#pragma once
#include <string>
#include <vector>
#include <set>
#include <memory>

class IMineMap;

class Labels
{
public:
	Labels(std::shared_ptr<IMineMap> mines, size_t size);
	~Labels();

	bool isUncovered(size_t boxId) const;
	std::string uncover(size_t boxId);


private:
	void populate();
	void updateTipsAround(size_t pos);
	void update3Row(size_t centerPos);

	std::shared_ptr<IMineMap> mines;
	size_t size;
	std::vector<int> labels;
	std::set<size_t> uncovered;
};

