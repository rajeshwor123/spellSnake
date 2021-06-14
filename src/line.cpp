#include "line.h"

line::line()
{
	size = 4 * sizeof(float);
	count = 2;
}
const void* line::vertexData()
{
	static float position[] = {0 , 560 , 800 , 560 };
	return position;
}
unsigned int* line::indicesData()
{
	static unsigned int indices[] = {0 , 1};
	return indices;
}