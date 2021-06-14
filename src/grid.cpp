#include "grid.h"
#include <GL/glew.h> 
#include<iostream>

static float position[9000];
unsigned int i = 0;
grid::grid() :count(0),size(0), width(0.0f), height(0.0f)
{

}
grid::~grid()
{

}

const void* grid::vertexData()
{
    //float* position = new float[];
   // static float position[7000];
    //unsigned int i = 0;
    
    for (float x = 0; x <= width; x = x + 20)
    {
        for (float y = 0; y <= height; y = y + 20)
        {
            position[i] = x;
            position[i + 1] = y;
            position[i + 2] = x + 20;
            position[i + 3] = y;
            position[i + 4] = x + 20;
            position[i + 5] = y + 20;
            position[i + 6] = x;
            position[i + 7] = y + 20;

            i = i + 8;
        }
    }
    size = i * sizeof(float);
    return position;
}

unsigned int* grid::indicesData()
{
    static unsigned int indices[7000];
    unsigned int i = 0;
    unsigned int offset = 0;
    for (float x = 0; x <=width; x = x + 20)
    {
        for (float y = 0; y <=height; y = y + 20)
        {
            indices[i] = 0 + offset;
            indices[i + 1] = 1 + offset;
            indices[i + 2] = 2 + offset;
            indices[i + 3] = 3 + offset;
            indices[i + 4] = 0 + offset;
           
            offset = offset + 4;
            i = i + 5;
        }
    }
    count = i;
    return indices;
}

