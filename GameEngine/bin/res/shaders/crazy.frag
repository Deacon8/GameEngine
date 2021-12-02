#version 430 core
out vec4 FragColor;
uniform float time;

void main()
{	
	float v = sin(time);
	float c = cos(time);
	float d = sin(cos(time));
	FragColor = vec4(v, c, d, 1.0f);
}