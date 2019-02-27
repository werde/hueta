#version 120 core

uniform sampler2D texSampler;
varying vec2 UV;

void main()
{
	//gl_FragColor = vec4(0.9, 0.3, 0.3, 0.5);
	gl_FragColor = texture2D(texSampler, UV);
}
