#version 120 core

uniform mat4 MVP;

attribute vec3 vertexPosition_modelspace;

varying vec2 UV;

void main()
{
	gl_Position = MVP*vec4(vertexPosition_modelspace, 1.0);
}
