#version 120 core

uniform mat4 MVP;

attribute vec3 vertexPosition_modelspace;

void main(){
	gl_Position = MVP*vec4(vertexPosition_modelspace, 1.0);
}