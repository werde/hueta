#version 120 core

uniform mat4 MVP;

attribute vec3 vertexPosition_modelspace;
attribute vec2 vertexUV;

varying vec2 UV;

void main(){
	gl_Position = MVP*vec4(vertexPosition_modelspace, 1.0);
	//vec2 test = vec2(1.0, 1.0);
	UV = vertexUV;
}