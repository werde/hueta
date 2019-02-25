#version 120 core

// Interpolated values from the vertex shaders
//in vec2 UV;

//uniform sampler2D myTextureSampler;

void main(){
	//gl_FragColor = texture( myTextureSampler, UV );
	
	// Hardcoded life level, should be in a separate texture.
	//if (UV.x < LifeLevel && UV.y > 0.3 && UV.y < 0.7 && UV.x > 0.04 )
	gl_FragColor = vec4(0.9, 0.9, 0.9, 1.0); // Opaque green
}