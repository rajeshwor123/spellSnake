#pragma once
#include "vertexBuffer.h"
class vertexBufferLayout;

class vertexArray 
{
private:

	unsigned int rendererId;

public:
	vertexArray();
	~vertexArray();
	void bind() const;
	void unbind() const;
	void addBuffer(const vertexBuffer& vb, const vertexBufferLayout& layout);

};