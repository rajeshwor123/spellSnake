#include "renderer.h"
#include <iostream>

void glClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool glLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "Opengl error : " << error << " function:" << function << " file:" << file << " line:" << line << std::endl;
        return false;
    }
    return true;
}

void renderer::draw(const vertexArray& va, const indexBuffer& ib, unsigned int drawType) const
{
    //binding everything and using draw call
    va.bind();
    ib.bind();
    glCall(glDrawElements(drawType, ib.getCount(), GL_UNSIGNED_INT, nullptr));

}

void renderer::clear() const
{

    glClear(GL_COLOR_BUFFER_BIT);

}
