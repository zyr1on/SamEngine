#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

#define MAX_LIGHTS 4

uniform int u_LightCount;
uniform vec3 u_LightPositions[MAX_LIGHTS];
uniform vec3 u_LightColors[MAX_LIGHTS];

uniform vec3 viewPos;
uniform sampler2D texture_diffuse1;

uniform float u_AmbientStrength;
uniform float u_SpecularStrength;
uniform float u_Shininess;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    vec3 ambient = u_AmbientStrength * vec3(1.0);
    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);
    
    // Her ışık için hesaplama
    for(int i = 0; i < u_LightCount; i++) {
        vec3 lightDir = normalize(u_LightPositions[i] - FragPos);
        
        // Diffuse
        float diff = max(dot(norm, lightDir), 0.0);
        diffuse += diff * u_LightColors[i];
        
        // Specular
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Shininess);
        specular += u_SpecularStrength * spec * u_LightColors[i];
    }
    
    vec3 result = (ambient + diffuse + specular) * texture(texture_diffuse1, TexCoord).rgb;
    FragColor = vec4(result, 1.0);
}