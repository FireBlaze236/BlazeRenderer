#version 330 core

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};
uniform Material material;

//Also requires texture coordinates
in vec3 fragPos;
in vec3 normal;
in vec2 texCoords;

out vec4 fragColor;


struct Light
{ 
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Light light;

uniform vec3 viewPos;

void main()
{
	//Ambient lighting

	vec3 ambient = vec3(texture(material.diffuse, texCoords)) * light.ambient;

	//Diffuse
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(light.position - fragPos);
	float diffuseAmount = max(dot(norm, lightDir), 0.0);

	vec3 diffuse = diffuseAmount * vec3(texture(material.diffuse, texCoords)) * light.diffuse;

	//Specular

	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float specularAmount = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	vec3 specular = vec3(texture(material.specular,texCoords)) * specularAmount * light.specular;
	

	vec3 result = (ambient + diffuse + specular);

	fragColor = vec4(result, 1.0);
}