#version 430 core

in vec2 uvs;
in vec3 normals;

uniform sampler2D intexture;

out vec4 FragColor;
void main()
{   
    //No Alpha for now
	FragColor = vec4(texture(intexture, uvs).rgb, 1.0f);
    
    //                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   FragColor = vec4(normals, 1.0f);
}