#version 330 core

out vec4 fragColor;

in vec3 currentPos;
in vec3 normal;
in vec3 color;
in vec2 texCoord;


uniform sampler2D diffuse0;
uniform vec4 lightColor;
uniform vec3 lightPos;


vec4 pointLight()
{	
	vec3 lightVec = lightPos - currentPos;

	float dist = length(lightVec);
	float a = 3.0;
	float b = 0.7;
	float intensity = 1.0f / (a * dist * dist + b * dist + 1.0f);

	float ambient = 0.20f;

	vec3 normal = normalize(normal);
	vec3 lightDirection = normalize(lightVec);

	float diffuse = max(dot(normal, lightDirection), 0.0f);

	return (texture(diffuse0, texCoord) * (diffuse * intensity + ambient)) * lightColor;
}

void main()
{
	
    fragColor = texture(diffuse0, texCoord);
}
