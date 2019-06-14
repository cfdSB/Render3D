#version 330 core
out vec4 FragColor;
uniform vec3 objectColor;
void main()
{
	vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
	vec3 result = objectColor;
	FragColor = vec4(result, 1.0f);
}