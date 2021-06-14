//#include <GL/glew.h>
#include "vertexBuffer.h"
#include "renderer.h"

vertexBuffer::vertexBuffer(const void* data, unsigned int size, unsigned int type) 
{

    glCall(glGenBuffers(1, &rendererID));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
    if (type == GL_STATIC_DRAW) 
    {
        glCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
    }else
    {
        glCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
    }

}
vertexBuffer::~vertexBuffer()
{

    glCall(glDeleteBuffers(1,&rendererID));

}

void vertexBuffer::bind() const
{

    glCall(glBindBuffer(GL_ARRAY_BUFFER, rendererID));

}
void vertexBuffer::unBind() const
{

    glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

}