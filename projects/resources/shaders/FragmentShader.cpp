#version 430
in vec2 ATexCoord;
in vec3 vs_normal;
in vec3 vs_pos;
in vec3 FragPos;


out vec4 Color;
uniform sampler2D ourTexture;

uniform vec3 light_color;
uniform vec3 lightPos0;
uniform vec3 cam_pos;
void main()
{
	//ambient light
	float ambientStrength = 0.1;
	vec3 ambient = light_color * ambientStrength;
	
	//diffuse light
	vec3 norm = normalize(vs_normal);
	vec3 lightDir = normalize(lightPos0 - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * light_color;

	//Specular
	float specularStrength = 0.5;
	vec3 viewDir = normalize(cam_pos - FragPos);
	vec3 halfwayDir = normalize(lightDir + viewDir);
	//vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(vs_normal, halfwayDir), 0.0), 32);
	vec3 specular = specularStrength * spec * light_color;

	vec3 result = ambient + diffuse + specular;// +specularFinal;
    Color = texture(ourTexture, ATexCoord) * (vec4(result, 1.0f));
}


//ambient är den ljusnivå man har utan någon direkt belysning
//diffuse är den huvudsakliga ljussättningen
//specular är glans 