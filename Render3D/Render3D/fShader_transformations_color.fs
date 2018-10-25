#version 330 core
in vec3 normal;
in vec3 fragPos;
out vec4 FragColor;
uniform vec3 lightPos;
uniform vec3 objectColor;
void main()
{
	
		//vec3 objectColor = vec3(1.0f, 0.5f, 0.2f);
		vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
		//ambient
		float ambientStrength = 0.1;
		vec3 ambient = ambientStrength*lightColor;
		//diffuse
		vec3 norm = normalize(normal);
		vec3 lightDir = normalize(lightPos - fragPos);
		//float diff = max(dot(norm, lightDir), 0.0);
		float diff = abs(dot(norm, lightDir));
		vec3 diffuse = diff*lightColor;
		vec3 result = (ambient+diffuse)*objectColor;
		FragColor = vec4(result, 1.0f);
	
}