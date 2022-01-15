#version 430 core

in vec2 uvs;
in vec3 normals;

uniform vec3 incolor;

out vec4 FragColor;
void main()
{   
    //No Alpha for now
	FragColor = vec4(incolor, 1.0f);
    
    //FragColor = vec4(normals, 1.0f);
}