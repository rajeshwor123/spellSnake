#pragma once
#include <GL/glew.h>
class vertexBuffer {
private:

	GLuint rendererID;
	//unsigned int rendererID;

public:

	vertexBuffer(const void* data, unsigned int size , unsigned int type);
	~vertexBuffer();

	void bind() const;
	void unBind() const;

	inline void invalidateBuffer()
	{
		glInvalidateBufferData(rendererID);
	}

	GLuint getBufferID() {
		return rendererID;
	}

};