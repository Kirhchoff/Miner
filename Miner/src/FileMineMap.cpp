#include "FileMineMap.h"
#include <fstream>


FileMineMap::FileMineMap(std::string filePath)
{
	std::ifstream file = std::ifstream(filePath);
	if (file.is_open())
	{
		while (!file.eof())
		{
			size_t input;
			file >> input;
			mines.insert(input);
		}
		file.close();
	}
}


bool FileMineMap::isMine(size_t position) const
{
	return mines.find(position) != mines.end();
}
