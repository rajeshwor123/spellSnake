#include "vertexArray.h"
#include "renderer.h"
#include "vertexBufferLayout.h"

vertexArray::vertexArray()
{
	glCall(glGenVertexArrays(1, &rendererId));
	
}
vertexArray::~vertexArray()
{
	glCall(glDeleteVertexArrays(1, &rendererId));
}

void vertexArray::bind() const
{
	glCall(glBindVertexArray(rendererId));

}
void vertexArray::unbind() const
{

	glCall(glBindVertexArray(0));

}

void vertexArray::addBuffer(const vertexBuffer& vb, const vertexBufferLayout& layout)
{
	bind();
	vb.bind();
	const auto& elements = layout.getElement();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		glCall(glEnableVertexAttribArray(i));
		glCall(glVertexAttribPointer(i, element.count, element.type, element.normal, layout.getStride(), (const void*) offset));
		offset += element.count * vertexBufferLayoutElement::getSizeOfType(element.type);
	}

}