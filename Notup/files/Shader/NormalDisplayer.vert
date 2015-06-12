#version 430

//the position of the vertex
in vec3 position;
//the normal of the vertex
in vec3 normal;

out vec3 vertexNorm;

//the output normal of the vertex
void main()
{
	vertexNorm = normal;
    //Process vertex
    gl_Position = vec4(position,1.0);
}
