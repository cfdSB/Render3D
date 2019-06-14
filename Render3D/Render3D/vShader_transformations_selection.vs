#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 2) in float id;

out float vId;

uniform mat4 mvpMat;

void main()
{
	vec4 v = vec4(aPos, 1.0);
	gl_Position = mvpMat*v;
	vId = id;
}