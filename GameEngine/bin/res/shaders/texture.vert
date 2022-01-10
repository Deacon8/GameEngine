#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 inuvs;
layout (location = 2) in vec3 innormals;

out vec2 uvs;
out vec3 normals;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{	
	uvs = inuvs;
	normals = innormals;
	gl_Position = projection * view * model * vec4(aPos, 1.0);
}