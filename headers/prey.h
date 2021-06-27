#pragma once
#include <snake.h>
#include <map>
class prey
{

private:
	std::map<char, unsigned int> charMap;
	std::map<unsigned int, unsigned int> scoreMap;
	std::map<std::pair<float, float>, unsigned int> coIndexMap;
	float spriteWidth;
	unsigned int collisionOrder;
	float randomCoordinates[20];
	unsigned int size;
	unsigned int count;
	unsigned int indexCountForCurrentLen;
	unsigned int indexOrder[10];
	unsigned int scoreIndex[6];
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
	const float* randomCoordinate(float snakeX, float snakeY);
	unsigned int* parseWordList();
	unsigned int* parseScore(unsigned int score);
	unsigned int matchRancoordinateWithIndex(float snakeX , float snakeY, bool boarderCollisionOrder, bool selfCollisionOrder);

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

	inline unsigned int indexCountForCurrentLength() {
		return indexCountForCurrentLen;
	}

	inline void clearMap() {
		coIndexMap.clear();
	}

};

