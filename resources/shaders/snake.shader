#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 textureCoordinate;

//out vec2 v_TextureCoordinate; //v stands for varying, simply we are outputting texture coordinates from vertex shader.
out vec2 fragCoordinate;

uniform vec2 v_TextureCoordinateShift;
uniform mat4 u_MVP;

void main()
{
 gl_Position =u_MVP * position;
 //v_TextureCoordinate = textureCoordinate;
 fragCoordinate = v_TextureCoordinateShift + textureCoordinate;

};



//remember fragment shader runs for every pixel

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

//in vec2 v_TextureCoordinate; //inputting texturecoordinates from vertex shader in fragment shader
in vec2 fragCoordinate;
uniform sampler2D u_Texture;

void main()
{
	//vec4 texColor = texture(u_Texture, v_TextureCoordinate);
	vec4 texColor = texture(u_Texture, fragCoordinate);
	color = texColor;
	//color = u_color;
};