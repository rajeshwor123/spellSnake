#pragma once
class line
{
private:
	unsigned int size;
	unsigned int count;
public:
	line();
	const void* vertexData();
	unsigned int* indicesData();

	inline unsigned int sizeOfData() {
		return size;
	}
	inline unsigned int countOfIndices() {
		return count;
	}
};

