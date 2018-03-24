#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
out vec3 normal;
out vec3 fragPos;
uniform mat4 projectionMat;
uniform mat4 viewMat;
void main()
{
	//gl_Position = vec4(aPos.x, aPos.y, aPos.z, aPos.w);
	vec4 v = vec4(aPos, 1.0);
	gl_Position = projectionMat*viewMat*v;
	normal = aNormal;
	fragPos = aPos;
}