#version 330 core

in float vId;
out vec4 FragColor;


void main()
{
	FragColor = vec4(vId, 0.0f, 0.0f, 1.0f);
}