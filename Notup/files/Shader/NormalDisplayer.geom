#version 430

layout(triangles) in;
layout(line_strip, max_vertices = 30) out;
//the projection matrix and model view matrix to transform the vertex
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 normalMatrix;
//the normal of the vertex
in vec3 vertexNorm[];
uniform float normalLength = 1f;
void main()
{
    mat4 mMVP = projectionMatrix * viewMatrix * modelMatrix;
	vec3 vPos = gl_in[0].gl_Position.xyz;
    vec3 currentPosition = vPos;
    for(int i = 0; i<3; ++i)
	{
		currentPosition = gl_in[i].gl_Position.xyz;
		vec3 vNormal = (normalMatrix * vec4(vertexNorm[i], 1.0)).xyz;
        gl_Position = mMVP*vec4(currentPosition, 1.0);
        EmitVertex();
        gl_Position = mMVP*vec4(currentPosition+vNormal * normalLength, 1.0);
        EmitVertex();
        EndPrimitive();
    }

	
}