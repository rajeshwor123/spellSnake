#pragma once
#include <snake.h>
#include <map>
class prey
{

private:
	std::map<char, unsigned int> charMap;
	std::map<std::pair<float, float>, unsigned int> coIndexMap;
	float spriteWidth;
	unsigned int collisionOrder;
	float randomCoordinates[20];
	unsigned int size;
	unsigned int count;
	unsigned int indexOrder[10];
	unsigned int ranWordLength;
	unsigned int indexCount;
	float coordinatesToBeRemoved[2];
public:
	prey();
	~prey()
	{

	}
	const void* vertexData();
	unsigned int* indicesData();
	const float* randomCoordinate();
	unsigned int* parseWordList();
	unsigned int matchRancoordinateWithIndex();

	inline unsigned int sizeOfData() {
		return size;
	}
	inline unsigned int countOfIndices() {
		return count;
	}

	inline void setCollisionOrder(unsigned int collision) {
		collisionOrder = collision;
	}

	inline unsigned int lengthOfRandomWord() {
		return ranWordLength;
	}

};

