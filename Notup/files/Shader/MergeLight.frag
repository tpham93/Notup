#version 430

//the coordinates of the texture
in vec2 texCoord;
// the final color
out vec4 fragColor;

// the color of the texture
uniform vec4 textureColor = vec4(1,1,1,1);

// the texture unit
layout(binding=0) uniform sampler2D groundTexture;

// the light unit
layout(binding=1) uniform sampler2D lightTexture;

void main()
{
	vec4 baseColor = texture(groundTexture, texCoord);
	vec4 lightColor = texture(lightTexture, texCoord);
	fragColor = vec4(mix(baseColor.xyz,baseColor.xyz * lightColor.xyz, (1.0-lightColor.z)),1.0) * textureColor;
}