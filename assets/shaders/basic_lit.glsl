#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos; 

// Işık ve Kamera Bilgileri
uniform vec3 lightPos;   // Işığın dünyadaki konumu
uniform vec3 viewPos;    // Kameranın dünyadaki konumu
uniform vec3 lightColor; // Işığın rengi (örn: vec3(1.0, 1.0, 1.0))
uniform sampler2D texture_diffuse1; // Objeye giydirdiğimiz doku

void main()
{
    // 1. Ambient (Ortam Aydınlatması - Her yerin çok az ışık alması)
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // 2. Diffuse (Yayılma Aydınlatması - Işığın yüzeye geliş açısı)    
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // 3. Specular (Yansıma/Parlama Aydınlatması - Kameranın açısına göre parlayan nokta)
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32); // 32 = Parlaklık (Shininess)
    vec3 specular = specularStrength * spec * lightColor;  

    // Sonuç: Doku rengiyle ışık bileşenlerini birleştiriyoruz
    vec3 result = (ambient + diffuse + specular) * texture(texture_diffuse1, TexCoord).rgb;
    FragColor = vec4(result, 1.0);
}