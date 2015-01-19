#version 400
layout (location = 0) in vec3 VertexPosition;  
layout (location = 1) in vec2 VertexUv;  
layout (location = 2) in vec3 VertexNormal;  

uniform mat4 MVP;
 
out vec3 position;  
out vec3 normal;  

void main()
{
	normal = VertexNormal;
	position =  VertexPosition;
	gl_Position = MVP * vec4( VertexPosition, 1.0);
}
