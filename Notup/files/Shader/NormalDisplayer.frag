#version 430

out vec4 outputColor;

uniform struct Material
{	
	//!	emission color
	sampler2D textureUnit;
	//!	emission color
	vec4 emission;
	//! diffuse color
	vec4 diffuse;
	//! ambient color
	vec4 ambient;
	//! specular color
	vec4 specular;
	//! the shininess
	float shininess;
} material;

void main()
{
	outputColor = material.emission * 0 + vec4(1.0 , 1.0 , 1.0 , 1.0);
}