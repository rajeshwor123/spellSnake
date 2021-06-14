#pragma once
class grid {

private:
	float width;
	float height;
	unsigned int size;
	unsigned int count;
public:
	grid();
	~grid();

	unsigned int* indicesData();
	const void* vertexData();

	inline void setGridSize(int x , int y){
		width = (float)x-20;
		height = (float)y - 60;
	}

	inline unsigned int sizeOfData() {
		return size;
	}
	inline unsigned int countOfIndices() {
		return count;
	}

};