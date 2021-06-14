#pragma once
#include<vector>
#include "vertexBuffer.h"
#include"GL/glew.h"
#include "renderer.h"

struct vertexBufferLayoutElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normal;

	static unsigned int getSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_UNSIGNED_BYTE: return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class  vertexBufferLayout
{
private:
	std::vector<vertexBufferLayoutElement> elements;
	unsigned int stride;

public:
	vertexBufferLayout() : stride(0) {};

	~vertexBufferLayout() {};

	template<typename T>
	void push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void push<float>(unsigned int count)
	{
		elements.push_back({GL_FLOAT,count,GL_FALSE});
		stride += count* vertexBufferLayoutElement::getSizeOfType(GL_FLOAT);
	}

	template<>
	void push<unsigned int>(unsigned int count)
	{
		elements.push_back({ GL_UNSIGNED_INT,count,GL_FALSE });
		stride += count*vertexBufferLayoutElement::getSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void push<unsigned char>(unsigned int count)
	{
		elements.push_back({ GL_UNSIGNED_BYTE,count,GL_TRUE });
		stride += count*vertexBufferLayoutElement::getSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<vertexBufferLayoutElement> getElement() const { return elements; }
	inline unsigned int getStride() const { return stride; }

};