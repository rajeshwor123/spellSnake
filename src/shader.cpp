#include "shader.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include "renderer.h"

shader::shader(const std::string& filePath):filePath(filePath),rendererId(0)
{
    snakeShader shaderObj = parseShader(filePath);
    rendererId = createShader(shaderObj.VertexShader, shaderObj.FragmentShader);
}
shader::~shader()
{
    glCall(glDeleteProgram(rendererId));
}

snakeShader shader::parseShader(const std::string& filepath) {
    std::ifstream stream(filepath);

    enum class shaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    shaderType type = shaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                //we found our vertex shader
                type = shaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                //we found our fragment shader
                type = shaderType::FRAGMENT;
            }
        }
        else
        {
            if (type != shaderType::NONE)
            {
                ss[(int)type] << line << '\n';
            }
            else
            {
                std::cout << "shader file is corrupt" << std::endl;
            }
        }
    }

    return { ss[0].str(), ss[1].str() };
}

//shader compilations:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
unsigned int shader:: compileShader(unsigned int type, const std::string& source) {

    unsigned int id = glCreateShader(type);
    const char* src = source.c_str(); //returning pointer to the begining of the data
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    //error handeling:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "failed to compile " << (type == GL_VERTEX_SHADER ? "vertex " : "fragment ") << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    return id;
}

 unsigned int shader::createShader(const std::string& vertexShader, const std::string& fragmentShader) {

    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int shader::getUniformLocations(const std::string& name) 
{
    if(uniformLocationCache.find(name) != uniformLocationCache.end())
    {
        return uniformLocationCache[name];
    }
    glCall(int location = glGetUniformLocation(rendererId, name.c_str()));
    if (location == -1)
    {
        std::cout << "warning : uniform  " << name << "doesn't exist " << std::endl;
    }
   
    uniformLocationCache[name] = location;
    return location;
}
void shader::bind() const
{
    glCall(glUseProgram(rendererId));
}
void shader::unbind() const
{
    glCall(glUseProgram(0));
}

void shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) 
{
    glCall(glUniform4f(getUniformLocations(name), v0, v1, v2, v3));//v0,v1... is colour codes
}

void shader::setUniformMatrix4fv(const std::string& name , const glm::mat4& matrix)
{
    glCall(glUniformMatrix4fv(getUniformLocations(name), 1, GL_FALSE, &matrix[0][0]));
}

void shader:: setUniform1i(const std::string& name, int value)
{

    glCall(glUniform1i(getUniformLocations(name), value));

}

void shader::setUniform2f(const std::string& name, float xShift, float yShift)
{

    glCall(glUniform2f(getUniformLocations(name), xShift , yShift));

}



