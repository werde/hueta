#version 120 core

attribute vec3 vertexPosition_modelspace;

uniform mat4 VP;

void main()
{
	gl_Position = VP * vec4(vertexPosition_modelspace, 1.0f);
}