#pragma once

class IMineMap
{
public:
	virtual ~IMineMap() = default;

	virtual bool isMine(size_t position) const = 0;
};
