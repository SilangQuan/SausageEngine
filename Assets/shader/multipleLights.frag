#version 400
const int MAX_POINT_LIGHTS = 5;                                                       

struct PointLight
{
	float range;
	vec3 pos;
	vec3 color;
	float intensity;
	float constant;
    float linear;
    float quadratic;  
};

struct MaterialInfo{  
    vec3 diffuse;  
    vec3 specular;  
    float shininess;  
};  

uniform vec3 ambient; 

uniform int pointLightCount; 
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform MaterialInfo materialInfo;
uniform vec3 cameraPosition;

in vec3 position;
in vec3 normal;
out vec4 finalColor;

vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.pos - fragPos);
	//ambient
	vec3 ambFactor = ambient;
	// Diffuse shading
	float diffFactor = max(dot(normal, lightDir), 0.0) * light.intensity ;
	// Specular shading
	vec3 reflectDir = normalize(reflect(-lightDir, normal));
	float specFactor = pow(max(dot(viewDir, reflectDir), 0.0), materialInfo.shininess) * light.intensity;
	// Attenuation
    float distance = length(light.pos - fragPos);
	float attenuation = 1.0f;
	if(distance < light.range)
	{
	    attenuation = 1.0f / (light.constant + light.linear * distance + 
  			    light.quadratic * (distance * distance));  
	}
	
	vec3 ambientColor = ambFactor;
	vec3 diffuseColor = diffFactor * materialInfo.diffuse * light.color;
	vec3 specularColor = specFactor * materialInfo.specular * light.color ;
	//return ambientColor + attenuation * (diffuseColor + specularColor);
	return attenuation * (diffuseColor + specularColor);
}


void main(void)
{
	vec3 totalLight = vec3(0,0,0);
	vec3 norm = normalize(normal);
	vec3 viewDir = normalize(cameraPosition - position);
	for(int i = 0; i < pointLightCount; i++)
	{
		totalLight += calculatePointLight(pointLights[i], normal, position, viewDir);
	}
	finalColor = vec4(totalLight, 1.0);
	return;
}
