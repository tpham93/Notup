#version 430

//the position of the vertex
in vec2 vertexPos2D;
//the coordinates of the texture
in vec2 textureCoord;
//the coordinates of the texture passed to the fragment shader
out vec2 texCoord;
//the coordinates of the texture passed to the fragment shader
out vec4 vertexCoord;

//the projection matrix and model view matrix to transform the vertex
uniform mat4 projectionMatrix = mat4(1.0);
uniform mat4 modelMatrix = mat4(1.0);
uniform mat4 viewMatrix = mat4(1.0);

void main()
{
	texCoord = textureCoord;
	vertexCoord =  projectionMatrix* viewMatrix*  modelMatrix*  vec4(vertexPos2D.x, vertexPos2D.y, 0.0, 1.0);
    //Process vertex
    gl_Position = projectionMatrix*  viewMatrix*  modelMatrix*  vec4(vertexPos2D.x, vertexPos2D.y, 0.0, 1.0);
}
