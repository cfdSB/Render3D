#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 normal;
out vec3 fragPos;

uniform mat4 mvpMat;

void main()
{
	vec4 v = vec4(aPos, 1.0);
	gl_Position = mvpMat*v;
	normal = aNormal;
	fragPos = aPos;
}