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
//OUTS
out vec4 fragColor;

//Lighting structs and functions
//Directional
struct DirLight
{
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
};
uniform DirLight dirLight;

//Point
struct PointLight
{
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
//uniform int pointLightCount;
#define POINT_LIGHTS 4
uniform PointLight pointLights[POINT_LIGHTS];



uniform vec3 viewPos;

//Lighting functions
vec3 CalculateDirectionalLight(DirLight light, vec3 normal, vec3 viewDir, in vec4 diffuseTexture, in vec4 specularTexture)
{
	vec3 lightDir = normalize(-light.direction);

	float diff = max(dot(normal, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir),0.0), material.shininess);

	//Results
	vec3 ambient = light.ambient * vec3(diffuseTexture);
	vec3 diffuse = light.diffuse * diff * vec3(diffuseTexture);
	vec3 specular = light.specular * spec * vec3(specularTexture);

	return (ambient + diffuse + specular);
}


vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, in vec4 diffuseTexture, in vec4 specularTexture)
{
	vec3 lightDir = normalize(light.position - fragPos);

	float diff = max(dot(normal, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	float dist = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));

	vec3 ambient = light.ambient * vec3(diffuseTexture);
	vec3 diffuse = light.diffuse * diff * vec3(diffuseTexture);
	vec3 specular = light.specular * spec * vec3(specularTexture);

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;


	return (ambient + diffuse * specular);
}


void main()
{
    vec3 norm = normalize(normal);
	vec3 viewDir = normalize(viewPos - fragPos);
	
	vec4 diffTex = texture(material.diffuse, texCoords);
	vec4 specTex = texture(material.specular, texCoords);

	vec3 result = CalculateDirectionalLight(dirLight, norm, viewDir, diffTex, specTex);

	for(int i = 0; i < POINT_LIGHTS; i++)
	{
		result += CalculatePointLight(pointLights[i], norm, fragPos, viewDir, diffTex, specTex);
	}

	fragColor = vec4(result, 1.0);
}
