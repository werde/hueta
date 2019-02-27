#version 120 core

attribute vec3 vertexPosition_modelspace;
attribute vec2 vertexUV;

varying vec2 UV;

void main()
{
	gl_Position = vec4(vertexPosition_modelspace, 1.0);
	UV = vertexUV;
}
