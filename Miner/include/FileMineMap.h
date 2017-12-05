#pragma once

#include "IMineMap.h"
#include <set>
#include <string>

class FileMineMap : public IMineMap
{
public:
	FileMineMap(std::string filePath);

	bool isMine(size_t position) const override;
private:
	std::set<size_t> mines;
};

