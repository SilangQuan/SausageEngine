#version 400
layout (location = 0) in vec3 VertexPosition;  
layout (location = 2) in vec2 VertexUv;  
layout (location = 2) in vec3 VertexNormal;  


uniform mat4 MVP;

out vec3 texCoord;

void main()
{
	texCoord = VertexUv;
    gl_Position = MVP * vec4( VertexPosition, 1.0);  
}
