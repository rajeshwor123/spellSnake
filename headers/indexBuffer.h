#pragma once
class indexBuffer {
private:

	unsigned int rendererID;
	unsigned int index_count;

public:

	indexBuffer(const unsigned int* data, unsigned int count , unsigned int type);
	~indexBuffer();

	void bind() const;
	void unBind() const;
	inline unsigned int getCount() const { return index_count; }
};