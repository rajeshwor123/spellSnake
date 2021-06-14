#pragma once
#include <iostream>
class snake
{

private:
	 float x[150];
	 float y[150];
	 unsigned int size;
	 unsigned int count;
	 int currentKey;
	 unsigned int indexCountForCurrentLen;
	 unsigned int collisionOrder;
	 bool boarderCollisionOrder;
	 unsigned int snakeLength;

public:
	snake();
	~snake()
	{
	
	}
	const void* vertexData();
	unsigned int* indicesData();
	void boarderCollision();
	unsigned int preyCollision();
	void gameOver();

	inline void setCurrentKey(int Key) {
		currentKey = Key;
	}

	inline float getXCoordinates() {
		return	x[0];
	}

	inline float getYCoordinates() {
		return	y[0];
	 }
	
	inline unsigned int sizeOfData() {
		return size;
	}
	inline unsigned int countOfIndices() {
		return count;
	}
	inline void setSnakeLength(unsigned int snakeLen) {
		snakeLength = snakeLen;
	}
	inline unsigned int indexCountForCurrentLength() {
		return indexCountForCurrentLen;
	}
	inline void setCollisionOrd(unsigned int Collision) {
		collisionOrder = Collision;
	}
};

