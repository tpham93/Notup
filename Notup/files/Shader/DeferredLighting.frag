#version 430

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
}
;
//the coordinates of the texture
in vec2 texCoord;
//the coordinates of the texture
in vec4 vertexCoord;
// the final color
out vec4 fragColor;
// the position of the camera
uniform vec3 cameraPos;
// the texture units
uniform sampler2D diffuseUnit;
uniform sampler2D normalUnit;
uniform sampler2D specularDataUnit;
uniform sampler2D materialDataUnit;
uniform sampler2D depthUnit;
uniform PointLight pointLight;
uniform float zNear;
uniform float zFar;
uniform mat4 viewMatrix3D = mat4(1.0);
uniform mat4 projectionMatrix3D = mat4(1.0);
uniform mat4 inverseProjectionViewMatrix = mat4(1.0);

const mat3 gX = mat3( 1, 0,-1,
					  2, 0,-2,
					  1, 0,-1);
const mat3 gY = mat3( 1, 2, 1,
					  0, 0, 0,
					 -1, 2,-1);

vec4 getPointLightLightening(vec4 pos, vec4 norm, vec3 cameraPos, PointLight pointLight, vec4 materialSpecular, float shininess, vec4 materialAmbient)
{
    vec4 vertexToLight = vec4(pointLight.position,1) - pos;
    float dist = length(vertexToLight);
    vertexToLight /= dist;
    vec4 ptColor = pointLight.color;
    float attenuationTotal = pointLight.constantAttenuationFactor + pointLight.linearAttenuationFactor * dist + pointLight.quadraticAttenuationFactor * dist * dist;
    ptColor = ptColor / attenuationTotal;
    ptColor.w = pointLight.color.a;
    vec4 diffuse = max(dot(norm,vertexToLight),0) * ptColor;
    vec4 vertexToCamera = normalize(vec4(cameraPos,1) - pos);
    vec4 r = reflect(-vertexToLight, norm);
    vec4 specular = vec4(0);
    if(shininess > 0)
	{
        specular = pow(max(dot(r, vertexToCamera),0),shininess) * ptColor * materialSpecular;
    }


	return (materialAmbient + diffuse + specular);
}


float calculateLinearDepth(float hyperbolicDepth)
{
    float depth = 2 * hyperbolicDepth - 1;
    depth = (depth * projectionMatrix3D[3][3] - projectionMatrix3D[3][2])/(depth * projectionMatrix3D[2][3] - projectionMatrix3D[2][2]);
    return (depth - zNear)/(zFar - zNear);
}


vec4 reconst_pos(vec2 dir,float depth)
{
    vec4 sPos = vec4(dir * 2.0 - 1.0, depth * 2.0 - 1.0, 1.0);
    sPos = inverseProjectionViewMatrix * sPos;
    sPos = sPos / sPos.w;
    return sPos;
}

void main()
{
    vec2 flippedTextureCoord		= vec2(texCoord.x,1-texCoord.y) ;
    vec4 textureColor				= texture(diffuseUnit, flippedTextureCoord);
    vec4 hyperbolicDepths			= texture(depthUnit, flippedTextureCoord);
    vec4 norm						= texture(normalUnit, flippedTextureCoord) * 2.0 - 1.0;
    vec4 specularData				= texture(specularDataUnit, flippedTextureCoord);
    vec4 materialData				= texture(materialDataUnit, flippedTextureCoord);
    float depth						= calculateLinearDepth(hyperbolicDepths.r);
    vec4 worldPos					= reconst_pos(flippedTextureCoord, hyperbolicDepths.r);
    vec4 materialSpecular			= vec4(specularData.rgb, 0.0);
    float shininess					= specularData.a;
    vec4 lighteningColor			= getPointLightLightening(worldPos, norm, cameraPos, pointLight, materialSpecular, shininess, materialData);

	fragColor = lighteningColor * textureColor;
	
	//vec2 sumNormalVal = vec2(0.0);
 //   float sumXY	= (0.0);
 //   float maxXY	= (0.0);


 //   for( int x = -1; x <= 1; ++x)
	//{
 //       for( int y = -1; y <= 1; ++y)
	//	{
	//		float dX = 2*x/800.0;
	//		float dY = 2*y/480.0;
	//		vec4 currentNorm = abs(texture(normalUnit, flippedTextureCoord + vec2(dX,dY)) * 2.0 - 1.0);
 //           float val = (currentNorm.x * currentNorm.y) * currentNorm.z;
	//		sumNormalVal += val * vec2((gX[x+1][y+1]),(gY[x+1][y+1]));
	//		maxXY = min(maxXY,abs(dot(currentNorm,vec4(1))));
 //       }
	//} 

	//sumXY = sumNormalVal.x * sumNormalVal.x + sumNormalVal.y * sumNormalVal.y;

	//if(sumXY >= 1.0)
	//{
	//	fragColor = vec4(0,0,0,baseColor.a);
	//}
	//else
	//{
	//	float colorIntensity = max(max(fragColor.x , fragColor.y), fragColor.z);
	//	fragColor.xyz = fragColor.xyz/colorIntensity;

	//	colorIntensity = clamp(float(int(colorIntensity) + 1)/2.0,0.0,1.0);
	//	fragColor.xyz = fragColor.xyz * colorIntensity;
	//	fragColor.a = baseColor.a;
	//}
}

