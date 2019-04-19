#version 120 core

uniform sampler2D myTextureSampler;
attribute vec2 vertexUV;

varying vec2 UV;

void main()
{
	//vec4 color = vec4(0.5,0.0,1.0,1.0);
	vec2 texCoords = vec2(UV);
	vec4 color = texture2D(myTextureSampler, UV);
	gl_FragColor = color;
}