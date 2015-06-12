#version 430

//the position of the vertex
in vec3 position;
//the coordinates of the texture
in vec3 normal;
//the coordinates of the texture
in vec2 textureCoord;
//the position of the vertex passed to the fragment shader
out vec4 worldPos;
//the normal of the vertex passed to the fragment shader
out vec4 norm;
//the coordinates of the texture passed to the fragment shader
out vec2 texCoord;

//the projection matrix and model view matrix to transform the vertex
uniform mat4 projectionMatrix = mat4(1.0);
uniform mat4 modelMatrix = mat4(1.0);
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 normalMatrix = mat4(1.0);

void main()
{
	worldPos  = (modelMatrix*  vec4(position, 1.0));
	norm = (modelMatrix* vec4(normal, 0.0));
	texCoord = textureCoord;

    //Process vertex
    gl_Position = projectionMatrix* viewMatrix* modelMatrix*  vec4(position, 1.0);
}
