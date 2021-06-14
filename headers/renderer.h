#pragma once
#include <GL/glew.h>
#include "vertexArray.h"
#include "indexBuffer.h"
#include "shader.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define glCall(x) glClearError();\
x;\
ASSERT(glLogCall(#x, __FILE__, __LINE__))

void glClearError();

bool glLogCall(const char* function, const char* file, int line);

class renderer
{
private:


public:
	void clear() const;
	void draw(const vertexArray& va, const indexBuffer& ib, unsigned int drawType) const;
};