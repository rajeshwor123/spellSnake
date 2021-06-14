#include <GL/glew.h>
#include "indexBuffer.h"
#include "renderer.h"

indexBuffer::indexBuffer(const unsigned int* data, unsigned int count, unsigned int type)
    :index_count(count) 
{
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));
    glCall(glGenBuffers(1, &rendererID));
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID));
    if (type == GL_STATIC_DRAW) {
        glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
    }
    else {
        glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_DYNAMIC_DRAW));
    }
}
indexBuffer::~indexBuffer()
{

    glCall(glDeleteBuffers(1, &rendererID));

}

void indexBuffer::bind() const
{

    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID));

}
void indexBuffer::unBind() const
{

    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

}