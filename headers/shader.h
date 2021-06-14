#pragma once
#include <string>
#include <unordered_map>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

struct snakeShader
{
	std::string VertexShader;
	std::string FragmentShader;
};

class shader
{

private:
	std::string filePath;
	unsigned int rendererId;
	std::unordered_map<std::string, int> uniformLocationCache;
	snakeShader parseShader(const std::string& filepath);
	unsigned int compileShader(unsigned int type, const std::string& source);
	unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
	int getUniformLocations(const std::string& name) ;

public:
	shader(const std::string& filePath);
	~shader();
	void bind() const;
	void unbind() const;
	void setUniform4f( const std::string& name, float v0, float v1, float v2, float v3) ;//colour codes
	void setUniformMatrix4fv(const std::string& name, const glm::mat4& matrix);
	void setUniform1i(const std::string& name, int value);
	void setUniform2f(const std::string& name, float xShift, float yShift);
};