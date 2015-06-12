#version 430

//the coordinates of the texture
in vec2 texCoord;
// the final color
out vec4 fragColor;

// the color of the texture
uniform vec4 textureColor = vec4(1,1,1,1);

// the texture unit
uniform sampler2D textureUnit;

void main()
{
	vec4 baseColor = texture(textureUnit, texCoord);
	fragColor = baseColor*  textureColor;
}