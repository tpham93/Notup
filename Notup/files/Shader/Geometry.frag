#version 430

//the position of the fragment in world space
in vec4 worldPos;
//the normal of the vertex
in vec4 norm;
//the coordinates of the texture
in vec2 texCoord;

// diffuse color
layout (location = 0) out vec4 diffuseOut;
// normal
layout (location = 1) out vec4 normalOut; 
// specular data
layout (location = 2) out vec4 specularDataOut; 
// material data
layout (location = 3) out vec4 materialDataOut; 

// the material of the current mesh
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
	diffuseOut = texture(material.textureUnit, texCoord);
	//worldPosOut = vec4((worldPos.rgb + vec3(100))/200,1);
	normalOut = (vec4(1) + vec4(normalize(norm).xyz,1))/2;
	specularDataOut = normalize(material.specular);
	specularDataOut.w = material.shininess;
	materialDataOut = material.emission + material.ambient;
}