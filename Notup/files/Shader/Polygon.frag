#version 430

//the position in world space
in vec4 worldPos;
//the position in view space
in vec4 viewPos;
//the normal of the vertex
in vec4 norm;
//the coordinates of the texture
in vec2 texCoord;
// the final color
out vec4 fragColor;

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

uniform struct PointLight
{	
	//!	the position of the pointlight
	vec3 position;
	//!	the color of the pointlight
	vec4 color;
	//! diffuse color
	float constantAttenuationFactor;
	//! ambient color
	float linearAttenuationFactor;
	//! specular color
	float quadraticAttenuationFactor;
} pointLight;

// the position of the camera
uniform vec3 cameraPos;

vec4 getPointLightLightening(vec4 pos, vec4 norm, vec3 cameraPos, PointLight pointLight, Material material)
{	
	vec4 vertexToLight = vec4(pointLight.position,0) - pos;
	float dist = length(vertexToLight);
	vertexToLight = normalize(vertexToLight);
	
	vec4 ptColor = pointLight.color;

	float attenuationTotal = pointLight.constantAttenuationFactor + pointLight.linearAttenuationFactor * dist + pointLight.quadraticAttenuationFactor * dist * dist;
	ptColor = ptColor / attenuationTotal;
	ptColor.w = pointLight.color.a;
	
	vec4 emissive = material.emission;
	vec4 diffuse = max(dot(normalize(norm),vertexToLight),0) * ptColor * material.diffuse;

	vec4 vertexToCamera = normalize(vec4(cameraPos,1) - pos);
	vec4 r = reflect(-vertexToLight, normalize(norm));
	vec4 specular = vec4(0);
	if(material.shininess > 0)
	{
		specular = pow(max(dot(r, vertexToCamera),0),material.shininess) * ptColor * material.specular;
	}
	return (emissive + material.ambient + diffuse + specular);
}

void main()
{
	vec4 textureColor = texture(material.textureUnit, texCoord);
	vec4 lighteningColor = getPointLightLightening(worldPos, norm, cameraPos, pointLight, material);
	fragColor = vec4((lighteningColor * textureColor).xyz,textureColor.w);
}